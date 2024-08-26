#include "Controller.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

Controller::Controller(QObject *parent)
    : QObject(parent), autoMode(false), timer(new QTimer) {
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
}

void Controller::setRepo(SensorRepository* r) {Repo = r;}
void Controller::setManager(SimulationManager* m) {Manager = m;}
void Controller::setView(SensorViewer* v) {view = v;}

Controller::~Controller() {delete timer;}

void Controller::add() const{
    // Mostra un dialogo per selezionare il tipo di sensore
    bool ok;
    QString sensorType = QInputDialog::getItem(nullptr, "Seleziona Tipo di Sensore",
                                               "Tipo di sensore:",
                                               QStringList() << "Temperatura" << "Torbidità" << "pH",
                                               0, false, &ok);
    if (!ok || sensorType.isEmpty()) {
        QMessageBox::warning(nullptr, "Aggiunta Annulata", "Nessun tipo di sensore selezionato.");
        return;
    }

    // Mostra un dialogo per inserire l'ID del sensore
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

        // Controllo che l'id non sia già assegnato ad un altro sensore
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

    // Mostra un dialogo per inserire il nome del sensore
    QString placeholder = "Sensore " + QString::number(id);
    QString name = QInputDialog::getText(nullptr, "Inserisci Nome del Sensore",
                                         "Nome del sensore:", QLineEdit::Normal, placeholder, &ok);
    if (!ok || name.isEmpty()) {
        QMessageBox::warning(nullptr, "Aggiunta Annulata", "Nome non valido.");
        return;
    }

    // Mostra un dialogo per inserire il valore iniziale del sensore
    float initialValue = QInputDialog::getDouble(nullptr, "Inserisci Valore Iniziale",
                                                 "Valore iniziale:", 0.0, -1e6, 1e6, 2, &ok);
    if (!ok) {
        QMessageBox::warning(nullptr, "Aggiunta Annulata", "Valore iniziale non valido.");
        return;
    }

    // Crea e aggiungi il sensore in base al tipo selezionato
    Sensor* newSensor = nullptr;
    if (sensorType == "Temperatura") {
        newSensor = new TempSensor(id, name, initialValue);
    } else if (sensorType == "Torbidità") {
        newSensor = new TurbSensor(id, name, initialValue);
    } else if (sensorType == "pH") {
        newSensor = new PHSensor(id, name, initialValue);
    }

    if (newSensor) {
        // Aggiungi il sensore al repository (presumendo esista una struttura per memorizzare sensori)
        Repo->addSensor(newSensor);

        // Notifica il SensorViewer dell'aggiunta del nuovo sensore
        if (view) {
            view->showSensor(newSensor);
            view->showSensorLists(Repo->getAllSensors());
        }

        // Aggiorna la vista o l'interfaccia utente come necessario
        // ...

        // Non dimenticare di liberare la memoria quando il sensore non è più necessario.
        // Questo dipende da come gestisci la vita degli oggetti sensori nel tuo repository.
        // Se `sensorRepository` possiede la responsabilità di liberare la memoria, non fare nulla qui.
    } else {
        QMessageBox::warning(nullptr, "Errore", "Impossibile creare il sensore.");
    }
}

void Controller::modify() const {

}


void Controller::remove() const {
    try
    {
        unsigned int sensorId = view->showRemoveDialog();  // Supponendo che la vista mostri un dialogo per scegliere il sensore da rimuovere
        Repo->removeSensor(sensorId);
        Sensor* s = Repo->getSensor();
        view->showSensor(s);  // Aggiorna la visualizzazione dei sensori
        view->showSensorLists(Repo->getAllSensors());
    }
    catch (std::runtime_error exc)
    {
        view->showWarning(exc.what());
    }
}

void Controller::Simulation() {

    try
    {
        unsigned int sensorId = view->showSelectDialog();  // Supponendo che la vista mostri un dialogo per scegliere il sensore da simulare

        // Recupera il sensore dal repository
        Sensor* sensor = Repo->searchSensor(sensorId);

        if (!sensor) {
            QMessageBox::warning(nullptr, "Errore", "Sensore non trovato.");
            return;
        }

        // Avvia la simulazione usando il SimulationManager
        Manager->runSimulation(sensor);

        // Se necessario, aggiorna la vista o esegui altre operazioni
        // ...
    }
    catch (std::runtime_error exc)
    {
        view->showWarning(exc.what());
    }
}

void Controller::selectSensor() const {
    try {
        unsigned int sensorId = view->showSelectDialog();  // Dialogo per selezionare il sensore
        Sensor* sensor = Repo->searchSensor(sensorId);
        if (sensor) {
            view->showSensor(sensor);
        } else {
            view->showWarning("Sensor not found.");
        }
    } catch (std::runtime_error& exc) {
        view->showWarning(exc.what());
    }
}

void Controller::search() const {
    try {
        unsigned int sensorId = view->showSearchDialog();  // Dialogo per cercare il sensore
        Sensor* sensor = Repo->searchSensor(sensorId);
        if (sensor) {
            view->showSensor(sensor);
        } else {
            view->showWarning("Sensor not found.");
        }
    } catch (std::runtime_error& exc) {
        view->showWarning(exc.what());
    }
}

void Controller::onSaveRequested() {
    QMessageBox::information(nullptr, "Salvataggio", "Funzionalità di salvataggio non implementata.");
}

void Controller::onModifyRequested() {
    QMessageBox::information(nullptr, "Modifica", "Funzionalità di modifica non implementata.");
}

void Controller::onDeleteRequested() {
    QMessageBox::information(nullptr, "Eliminazione", "Funzionalità di eliminazione non implementata.");
}

void Controller::onSimulationRequested() {
    // Implementa la logica per avviare una simulazione
    // Potresti chiedere all'utente di selezionare un sensore e poi eseguire la simulazione
    unsigned int sensorId = 1; // Esempio: recupera un ID sensore in qualche modo
    if (Manager) {
        Manager->runSimulation(Repo->searchSensor(sensorId));
    }
}

void Controller::open() {

}

void Controller::close() {
    QCoreApplication::quit();
}

void Controller::save() {
    // Implementazione per salvare lo stato
    //qDebug() << "Save action triggered";

    QFileDialog dialog(view, "Salva boh", "", "JSON file (*.json)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("json");
    dialog.exec();
}

/*
void Controller::addSensor(const QString& sensorType, unsigned int id, const QString& name, float value) {
    // Implementazione per aggiungere un sensore
    // Esempio:
    Sensor* sensor = nullptr;
    if (sensorType == "Temperatura") {
        sensor = new TempSensor(id, name, value);
    } else if (sensorType == "Torbidità") {
        sensor = new TurbSensor(id, name, value);
    } else if (sensorType == "pH") {
        sensor = new PHSensor(id, name, value);
    }
    if (sensor) {
        // Aggiungi sensore al repository (da implementare)
        //emit sensorAdded(sensor);
    }
}
*/
