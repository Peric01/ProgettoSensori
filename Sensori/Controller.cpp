#include "Controller.h"
#include "FileConverter.h"
#include "GraphBars.h"
#include "GraphSmoothLine.h"
#include <GraphArea.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <stdexcept>


Controller::Controller(QObject *parent)
    : QObject(parent), autoMode(false), timer(new QTimer) {
    selectedSensor = nullptr;
}

void Controller::setRepo(SensorRepository* r) {Repo = r;}
void Controller::setView(SensorViewer* v) {view = v;}

Controller::~Controller() {
    delete timer;
    delete selectedSensor;
    delete view;
    delete Repo;
}

void Controller::add(){
    Sensor* newSensor = nullptr;
    bool ok;
    QString sensorType = QInputDialog::getItem(nullptr, "Seleziona Tipo di Sensore",
                                               "Tipo di sensore:",
                                               QStringList() << "Temperatura" << "Torbidità" << "pH",
                                               0, false, &ok);
    if (!ok || sensorType.isEmpty()) {
        QMessageBox::warning(nullptr, "Aggiunta Annulata", "Nessun tipo di sensore selezionato.");
        return;
    }

    bool cercaNuovoId = true;
    unsigned int id;
    while(cercaNuovoId)
    {
        id = QInputDialog::getInt(nullptr, "Inserisci ID del Sensore",
                                               "ID del sensore:", 1, 1, 10000, 1, &ok);
        if (!ok) {
            QMessageBox::warning(nullptr, "Aggiunta Annulata", "ID non valido.");
            return;
        }

        cercaNuovoId = false;
        for(auto s : Repo->getAllSensors())
        {
            if(s->getID() == id)
            {
                cercaNuovoId = true;
                QMessageBox::warning(nullptr, "Aggiunta Annulata", "ID già utilizzato.");
            }
        }
    }

    QString placeholder;
    if (sensorType == "Temperatura") {
        placeholder = "Temp" + QString::number(id);
    } else if (sensorType == "Torbidità") {
        placeholder = "Turb" + QString::number(id);
    } else if (sensorType == "pH") {
        placeholder = "pH" + QString::number(id);
    }
    bool cercaNuovoNome = true;
    QString name;
    while(cercaNuovoNome)
    {
        name = QInputDialog::getText(nullptr, "Inserisci Nome del Sensore","Nome del sensore:", QLineEdit::Normal, placeholder, &ok);
        if (!ok || name.isEmpty()) {
            QMessageBox::warning(nullptr, "Aggiunta Annulata", "Nome non valido.");
            return;
        }

        cercaNuovoNome = false;
        for(auto s : Repo->getAllSensors())
        {
            if(s->getName() == name.toStdString())
            {
                cercaNuovoNome = true;
                QMessageBox::warning(nullptr, "Aggiunta Annullata", "Nome già utilizzato.");
            }
        }
    }

    float initialValue;
    bool newInit = true;
    while (newInit){
        initialValue = QInputDialog::getDouble(nullptr, "Inserisci Valore Iniziale","Valore iniziale:", 1.0, -50, 4000, 2, &ok);
        if (!ok) {
            QMessageBox::warning(nullptr, "Aggiunta Annulata", "Valore iniziale non valido.");
            return;
        }
        newInit = false;
        if (sensorType == "Temperatura") {
            if(initialValue < -50 || initialValue > 250){
                newInit = true;
                QMessageBox::warning(nullptr, "Aggiunta Annullata", "Inserire un valore tra -50 e 250");
            }
        } else if (sensorType == "Torbidità") {
            if(initialValue < 0.01 || initialValue > 4000){
                newInit = true;
                QMessageBox::warning(nullptr, "Aggiunta Annullata", "Inserire un valore tra 0.01 e 4000");
            }
        } else if (sensorType == "pH") {
            if(initialValue < 0.01 || initialValue > 14){
                newInit = true;
                QMessageBox::warning(nullptr, "Aggiunta Annullata", "Inserire un valore tra 0.01 e 14");
            }
        }
    }


    if (sensorType == "Temperatura") {
        newSensor = new TempSensor(id, name, initialValue);
    } else if (sensorType == "Torbidità") {
        newSensor = new TurbSensor(id, name, initialValue);
    } else if (sensorType == "pH") {
        newSensor = new PHSensor(id, name, initialValue);
    }

    if (newSensor) {
        Repo->addSensor(newSensor);
        selectedSensor = newSensor;
        if (view) {
            view->showSensor(newSensor);
            view->showSensorLists(Repo->getAllSensors());
            view->clearGraph();
        }
    } else {
        QMessageBox::warning(nullptr, "Errore", "Impossibile creare il sensore.");
    }
}


void Controller::remove(){
    try
    {
        unsigned int sensorID;
        if(!Repo->getEmpty()){
            sensorID = view->showRemoveDialog();
            Repo->removeSensor(sensorID);
            view->showSensorLists(Repo->getAllSensors());
            view->clearData();
            view->clearGraph();
            selectedSensor = nullptr;
        }
        else
            throw std::runtime_error("");
    }
    catch (std::runtime_error& exc)
    {
        view->showWarning("Nessun sensore presente");
    }
}

void Controller::Simulation() {

    try
    {
        if (!selectedSensor) {
            view->showWarning("Sensore non selezionato");
            return;
        }
        else{
            TempSensor* tp = dynamic_cast<TempSensor*>(selectedSensor);
            PHSensor* ph = dynamic_cast<PHSensor*>(selectedSensor);
            TurbSensor* tb = dynamic_cast<TurbSensor*>(selectedSensor);
            if(tp){
                if(tp->getAllValues().size() <= 1){
                    view->showWarning("Aggiungi piu valori al sensore");
                    return;
                }
                GraphSmoothLine tempgraph;
                tempgraph.setGraph(tp);
                view->showGraph(tempgraph.getGraph());
            }
            else if(ph){
                if(ph->getAllValues().size() <= 1){
                    view->showWarning("Aggiungi piu valori al sensore");
                    return;
                }
                GraphArea phgraph;
                phgraph.setGraph(ph);
                view->showGraph(phgraph.getGraph());
            }
            else if(tb){
                if(tb->getAllValues().empty()){
                    view->showWarning("Aggiungi piu valori al sensore");
                    return;
                }
                GraphBars turbgraph;
                turbgraph.setGraph(tb);
                view->showGraph(turbgraph.getGraph());
            }
        }
    }
    catch (std::runtime_error& exc)
    {
        view->showWarning(exc.what());
    }
}

void Controller::randSimulation() {

    try
    {
        if (!selectedSensor) {
            view->showWarning("Nessun tipo di sensore selezionato");
            return;
        }
        else{
            TempSensor* tp = dynamic_cast<TempSensor*>(selectedSensor);
            PHSensor* ph = dynamic_cast<PHSensor*>(selectedSensor);
            TurbSensor* tb = dynamic_cast<TurbSensor*>(selectedSensor);
            if(tp){
                GraphSmoothLine tempgraph;
                tempgraph.setRandGraph(tp);
                view->showGraph(tempgraph.getGraph());
            }
            else if(ph){
                GraphArea phgraph;
                phgraph.setRandGraph(ph);
                view->showGraph(phgraph.getGraph());
            }
            else if(tb){
                GraphBars turbgraph;
                turbgraph.setRandGraph(tb);
                view->showGraph(turbgraph.getGraph());
            }
        }
    }
    catch (std::runtime_error& exc)
    {
        view->showWarning(exc.what());
    }
}

void Controller::selectSensor() {
    try {
        unsigned int sensorID;
        if(!Repo->getEmpty()){
            sensorID = view->showSelectDialog();
            selectedSensor = Repo->searchSensor(sensorID);
            if (selectedSensor) {
                view->showSensor(selectedSensor);
                view->clearGraph();
            } else {
                view->showWarning("Sensore inesistente");
            }
        }
        else
            view->showWarning("Nessun sensore presente");
    } catch (std::runtime_error& exc) {
        view->showWarning("Nessun sensore selezionato");
    }
}

void Controller::popValue(){
    try{
        if(!selectedSensor){
            view->showWarning("Seleziona o crea un sensore");
        }
        else {
            selectedSensor->removeLastValue();
            selectedSensor->updateMaxValue();
            selectedSensor->updateMinValue();
            view->showSensor(selectedSensor);
            view->showSensorLists(Repo->getAllSensors());
        }
    }  catch (std::runtime_error& exc) {
        view->showWarning(exc.what());
    }
}

void Controller::pushValue(){
    try{
        if(!selectedSensor){
            view->showWarning("Seleziona o crea un sensore");
        }
        else{
            float valuetoAdd = view->showValueDialog();
            if(valuetoAdd < selectedSensor->getTolMin() || valuetoAdd > selectedSensor->getTolMax()) {
                view->showWarning("Fornire un valore tra " + QString::number(selectedSensor->getTolMin()) + " e " + QString::number(selectedSensor->getTolMax()));
                return;
            }
            selectedSensor->addValue(valuetoAdd);
            selectedSensor->updateMaxValue();
            selectedSensor->updateMinValue();
            view->showSensor(selectedSensor);
            view->showSensorLists(Repo->getAllSensors());
        }

    }  catch (std::runtime_error& exc) {
        view->showWarning(exc.what());
    }
}

void Controller::open() {
    try {
        QString path = QFileDialog::getOpenFileName(
            view,
            "Apri sensori",
            "",
            "JSON file (*.json)"
            );

        if (path.isEmpty()) {
            return;
        }


        QJsonObject jsonSensors = FileConverter::readJsonObjectFromFile(path);

        if (jsonSensors.contains("sensors") && jsonSensors["sensors"].isArray()) {
            QJsonArray sensorArray = jsonSensors["sensors"].toArray();
            std::vector<Sensor*> sensors;

            for (const auto& sensorValue : sensorArray) {
                QJsonObject sensorObj = sensorValue.toObject();
                Sensor* sensor = FileConverter::JsonObjectToSensor(sensorObj);
                sensors.push_back(sensor);
            }

            Repo->setAllSensors(sensors);

            view->clearData();
            view->showSensorLists(Repo->getAllSensors());
            view->clearGraph();
        } else {
            throw std::runtime_error("Il file JSON non contiene dati sui sensori.");
        }
    }
    catch (const std::runtime_error& exc) {
        QMessageBox::warning(view, "Errore", exc.what());
    }
}


void Controller::save() {
    try {
        QString path = QFileDialog::getSaveFileName(
            view,
            "Salva sensori",
            "",
            "JSON file (*.json)"
            );

        if (path.isEmpty()) {
            return;
        }

        QJsonObject jsonSensors;
        QJsonArray sensorArray;
        for (const auto& sensor : Repo->getAllSensors()) {
            sensorArray.append(FileConverter::SensorToJsonObject(*sensor));
        }
        jsonSensors.insert("sensors", sensorArray);


        FileConverter::saveJsonObjectToFile(path, jsonSensors);


        QMessageBox::information(view, "Salva sensori", "Sensori salvati correttamente");
    }
    catch (const std::runtime_error& exc) {

        QMessageBox::warning(view, "Errore", exc.what());
    }
}


void Controller::close() {
    QCoreApplication::quit();
}

