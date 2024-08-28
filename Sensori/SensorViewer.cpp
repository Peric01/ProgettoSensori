#include "SensorViewer.h"
#include "TempSensor.h"
#include "TurbSensor.h"
#include "PHSensor.h"
#include "Controller.h"
#include <QInputDialog>
#include <QPalette>
#include <QColor>

void SensorViewer::clearLayout(QLayout* layout) const{
    QLayoutItem* item;
    while((item = layout->takeAt(0))){
        if(item->layout()){
            clearLayout(item->layout());
        }
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }
}


void SensorViewer::showSensor(Sensor* s) {
    // Ripuliamo i layout dati dal sensore precedente
    clearLayout(staticBox);
    clearLayout(editableBox);

    // Creiamo delle QLabel per mostrare le informazioni del sensore

    QString min = "N/a";
    QString max = "N/a";
    QString cur = "N/a";
    if(!s->isEmpty())
    {
        min = QString::number(s->getMin());
        max = QString::number(s->getMax());
        cur = QString::number(s->getCurrentValue());
    }

    QLabel* nameLabel = new QLabel("Nome: " + QString::fromStdString(s->getName()), this);
    QLabel* idLabel = new QLabel("ID: " + QString::number(s->getID()), this);
    QLabel* minValueLabel = new QLabel("Valore Minimo: " + min, this);
    QLabel* maxValueLabel = new QLabel("Valore Massimo: " + max, this);
    QLabel* currentValueLabel = new QLabel("Valore Corrente: " + cur, this);

    // Aggiungiamo le QLabel al layout principale
    staticBox->addWidget(nameLabel);
    staticBox->addWidget(idLabel);

    editableBox->addWidget(minValueLabel);
    editableBox->addWidget(maxValueLabel);
    editableBox->addWidget(currentValueLabel);

    // Determiniamo il tipo di sensore e aggiungiamo le informazioni specifiche
    QString type = "Tipo: ";
    TempSensor* tp = dynamic_cast<TempSensor*>(s);
    TurbSensor* tb = dynamic_cast<TurbSensor*>(s);
    PHSensor* ph = dynamic_cast<PHSensor*>(s);
    if (tp) {
        type += "Temperatura";
    }
    else if (tb) {
        type += "Torbidità";
    }
    else if (ph) {
        type += "pH";
    }

    QLabel* typeLabel = new QLabel(type, this);
    staticBox->addWidget(typeLabel);

    // Aggiorniamo la visualizzazione
    staticBox->update();
}


void SensorViewer::addMenus(QVBoxLayout* mainLayout)
{
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File", menuBar);
    menuBar->addMenu(file);
    QMenu* NewSensor = new QMenu("Gestione Sensori", menuBar);
    menuBar->addMenu(NewSensor);

    // Menu/Gestione File
    saveAction = new QAction("Salva", file);
    openAction = new QAction("Apri", file);
    closeAction = new QAction("Chiudi", file);

    file->addAction(saveAction);
    file->addAction(openAction);
    file->addAction(closeAction);

    // Menu/Aggiunta Sensori
    addAction = new QAction("Aggiungi", NewSensor);
    deleteAction = new QAction("Elimina", NewSensor);
    selectAction = new QAction("Seleziona", NewSensor);
    NewSensor->addAction(addAction);
    NewSensor->addAction(deleteAction);
    NewSensor->addAction(selectAction);

    mainLayout->addWidget(menuBar);

    // Menu/Barra di ricerca nel Menu
    QLineEdit* searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");
    menuBar->setCornerWidget(searchBar);
}

void SensorViewer::showSensorLists(std::vector<Sensor*> sensors)
{
    clearLayout(temperatureLayout);
    clearLayout(turbidityLayout);
    clearLayout(phLayout);

    QLabel* temperatureLabel = new QLabel("Temperature Sensors", this);
    temperatureLayout->addWidget(temperatureLabel);
    temperatureLabel->setMaximumHeight(20);
    temperatureLabel->setStyleSheet("background-color: magenta;");

    QLabel* turbidityLabel = new QLabel("Turbidity Sensors", this);
    turbidityLayout->addWidget(turbidityLabel);
    turbidityLabel->setMaximumHeight(20);
    turbidityLabel->setStyleSheet("background-color: lightgreen;");

    QLabel* phLabel = new QLabel("pH Sensors", this);
    phLayout->addWidget(phLabel);
    phLabel->setMaximumHeight(20);
    phLabel->setStyleSheet("background-color: orange;");


    for(auto s : sensors)
    {
        TempSensor* tp = dynamic_cast<TempSensor*>(s);
        TurbSensor* tb = dynamic_cast<TurbSensor*>(s);
        PHSensor* ph = dynamic_cast<PHSensor*>(s);

        QLabel* label = new QLabel(QString::fromStdString(s->getName()), this);
        label->setMaximumHeight(20);  // Imposta l'altezza massima per ciascuna QLabel
        if (tp) {
            temperatureLayout->addWidget(label);
        }
        else if (tb) {
            turbidityLayout->addWidget(label);
        }
        else if (ph) {
            phLayout->addWidget(label);
        }
    }

    temperatureLayout->update();
    turbidityLayout->update();
    phLayout->update();
}

void SensorViewer::addSensors(QVBoxLayout* sensorLayout)
{
    temperatureLayout = new QVBoxLayout;
    temperatureLayout->setAlignment(Qt::AlignTop);

    QLabel* temperatureLabel = new QLabel("Temperature Sensors", this);
    temperatureLayout->addWidget(temperatureLabel);
    temperatureLabel->setMaximumHeight(20);

    // Scroll area per i sensori di temperatura
    QScrollArea* temperatureScrollArea = new QScrollArea(this);
    QWidget* temperatureWidget = new QWidget();
    temperatureWidget->setLayout(temperatureLayout);
    temperatureScrollArea->setWidget(temperatureWidget);
    temperatureScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(temperatureScrollArea);

    // Sezione per i sensori di torbidità
    turbidityLayout = new QVBoxLayout;
    turbidityLayout->setAlignment(Qt::AlignTop);

    QLabel* turbidityLabel = new QLabel("Turbidity Sensors", this);
    turbidityLayout->addWidget(turbidityLabel);
    turbidityLabel->setMaximumHeight(20);


    // Scroll area per i sensori di torbidità
    QScrollArea* turbidityScrollArea = new QScrollArea(this);
    QWidget* turbidityWidget = new QWidget();
    turbidityWidget->setLayout(turbidityLayout);
    turbidityScrollArea->setWidget(turbidityWidget);
    turbidityScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(turbidityScrollArea);

    // Sezione per i sensori di pH
    phLayout = new QVBoxLayout;
    phLayout->setAlignment(Qt::AlignTop);

    QLabel* phLabel = new QLabel("pH Sensors", this);
    phLayout->addWidget(phLabel);
    phLabel->setMaximumHeight(20);

    // Scroll area per i sensori di pH
    QScrollArea* phScrollArea = new QScrollArea(this);
    QWidget* phWidget = new QWidget();
    phWidget->setLayout(phLayout);
    phScrollArea->setWidget(phWidget);
    phScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(phScrollArea);
}

void SensorViewer::clearData() {
    // Pulisce i layout staticBox e editableBox
    if (staticBox) {
        clearLayout(staticBox);

        // Aggiungi più QLabel per Nome, ID e Tipo
        QLabel* nameLabel = new QLabel("Nome: ", this);
        QLabel* idLabel = new QLabel("ID: ", this);
        QLabel* typeLabel = new QLabel("Tipo: ", this);

        staticBox->addWidget(nameLabel);
        staticBox->addWidget(idLabel);
        staticBox->addWidget(typeLabel);
    }
    if (editableBox) {
        clearLayout(editableBox);
        QLabel* minLabel = new QLabel("Valore Minimo: ", this);
        QLabel* maxLabel = new QLabel("Valore Massimo: ", this);
        QLabel* curLabel = new QLabel("Valore Corrente: ", this);

        editableBox->addWidget(minLabel);
        editableBox->addWidget(maxLabel);
        editableBox->addWidget(curLabel);
    }
}


void SensorViewer::addData(QHBoxLayout* dataLayout)
{
    // Crea i layout per i dati statici e modificabili
    staticBox = new QVBoxLayout;
    editableBox = new QVBoxLayout;

    // Pulisce i layout dai dati precedenti
    clearData();

    // Incapsula ciascun layout in un QFrame
    QFrame* staticFrame = new QFrame(this);
    staticFrame->setLayout(staticBox);
    staticFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    staticFrame->setStyleSheet("border: 1px solid black;");

    QFrame* editableFrame = new QFrame(this);
    editableFrame->setLayout(editableBox);
    editableFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    editableFrame->setStyleSheet("border: 1px solid black;");

    // Aggiungi i QFrame al layout principale
    dataLayout->addWidget(staticFrame);
    dataLayout->addWidget(editableFrame);
}

void SensorViewer::addButtons(QVBoxLayout* buttonLayout)
{
    addValueButton = new QPushButton("Aggiungi un valore", this);
    removeLastValueButton = new QPushButton("Rimuovi l'ultimo valore", this);
    runSimulationButton = new QPushButton("Lancia Simulazione", this);
    addValueButton->setObjectName("addValueButton");
    removeLastValueButton->setObjectName("removeLastValueButton");
    runSimulationButton->setObjectName("runSimulationButton");

    buttonLayout->addWidget(addValueButton);
    buttonLayout->addWidget(removeLastValueButton);
    buttonLayout->addWidget(runSimulationButton);
}


QFrame* SensorViewer::addGraph()
{
    QFrame* graphFrame = new QFrame(this);
    graphFrame->setFrameStyle(QFrame::Box);
    graphFrame->setStyleSheet("border: 2px solid black;");
    QVBoxLayout* graphLayout = new QVBoxLayout;
    QLabel* graphLabel = new QLabel("Simulazione di grafico dei valori del sensore", this);
    graphFrame->setLayout(graphLayout);
    graphLayout->addWidget(graphLabel);

    return graphFrame;
}


SensorViewer::SensorViewer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* screenLayout = new QHBoxLayout;  // Layout principale: due colonne (sinistra e destra)

    QVBoxLayout* sensorLayout = new QVBoxLayout;  // Layout verticale per i sensori
    QFrame* sensorFrame = new QFrame(this);
    sensorFrame->setFrameStyle(QFrame::Box);
    sensorFrame->setStyleSheet("border: 2px solid black;");
    sensorFrame->setLayout(sensorLayout);

    QVBoxLayout* dataAndGraphLayout = new QVBoxLayout; // Layout verticale per dati e grafico

    QHBoxLayout* dataAndButtonsLayout = new QHBoxLayout;  // Layout orizzontale per dati e pulsanti

    QVBoxLayout* buttonLayout = new QVBoxLayout; // Layout verticale per i pulsanti

    // Menu
    addMenus(mainLayout);

    // Sezione per i sensori
    addSensors(sensorLayout);

    // Aggiungi i dati e i pulsanti
    addData(dataAndButtonsLayout);
    addButtons(buttonLayout);
    dataAndButtonsLayout->addLayout(buttonLayout);


    QFrame* graphFrame = addGraph();
    dataAndGraphLayout->addLayout(dataAndButtonsLayout, 1);
    dataAndGraphLayout->addWidget(graphFrame, 1);

    screenLayout->addWidget(sensorFrame, 1);
    screenLayout->addLayout(dataAndGraphLayout, 2);

    mainLayout->addLayout(screenLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(1024, 720));
}

void SensorViewer::showWarning(const QString& message){
    QDialog* dialog = new QDialog(this);
    dialog->setLayout(new QHBoxLayout);
    dialog->layout()->addWidget(new QLabel(message, dialog));
    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->setMinimumWidth(200);
    dialog->setMaximumWidth(500);
    dialog->show();
}

QString SensorViewer::showAddDialog(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Apri il File"), "/home");
    if (fileName == "")
        throw std::runtime_error("Nessun file scelto: aggiunta annullata");
    return fileName;
}



void SensorViewer::setController(Controller* c) {
    controller = c;

    connect(addValueButton, SIGNAL(clicked(bool)), controller, SLOT(pushValue()));
    connect(removeLastValueButton, SIGNAL(clicked(bool)), controller, SLOT(popValue()));
    connect(runSimulationButton, SIGNAL(clicked(bool)), controller, SLOT(Simulation()));

    // menù/gestione file
    connect(saveAction, SIGNAL(triggered()), controller, SLOT(save()));
    connect(openAction, SIGNAL(triggered()), controller, SLOT(open()));
    connect(closeAction, SIGNAL(triggered()), controller, SLOT(close()));
    // menù/gestione sensori
    connect(addAction, SIGNAL(triggered(bool)), controller, SLOT(add()));
    connect(deleteAction, SIGNAL(triggered(bool)), controller, SLOT(remove()));
    connect(selectAction, SIGNAL(triggered(bool)), controller, SLOT(selectSensor()));

}


unsigned int SensorViewer::showRemoveDialog() {
    // Implementa un dialogo per selezionare il sensore da rimuovere
    bool ok;
    unsigned int sensorId = QInputDialog::getInt(this, tr("Rimuovi Sensore"),
                                                 tr("Inserisci l'ID del sensore:"), 1, 0, 100, 1, &ok);
    if (ok) {
        return sensorId;
    } else {
        throw std::runtime_error("Rimozione annullata");
    }
}

unsigned int SensorViewer::showSelectDialog() {
    // Implementa un dialogo per selezionare un sensore
    bool ok;
    unsigned int sensorId = QInputDialog::getInt(this, tr("Seleziona Sensore"),
                                                 tr("Inserisci l'ID del sensore:"), 1, 0, 100, 1, &ok);
    if (ok) {
        return sensorId;
    } else {
        throw std::runtime_error("Selezione annullata");
    }
}


float SensorViewer::showValueDialog(){
    bool ok;
    float value = static_cast<float>(QInputDialog::getDouble(this, tr("Aggiungi Valore"),
                                                             tr("Inserisci il nuovo valore del sensore:"),
                                                             0.0,   // valore predefinito
                                                             -10000.0, // valore minimo
                                                             10000.0,  // valore massimo
                                                             2, // numero di decimali
                                                             &ok));
    if (ok) {
        return value;
    } else {
        throw std::runtime_error("Selezione annullata");
    }
}

unsigned int SensorViewer::showSearchDialog() {
    // Implementa un dialogo per cercare un sensore
    bool ok;
    unsigned int sensorId = QInputDialog::getInt(this, tr("Cerca Sensore"),
                                                 tr("Inserisci l'ID del sensore:"), 1, 0, 100, 1, &ok);
    if (ok) {
        return sensorId;
    } else {
        throw std::runtime_error("Ricerca annullata");
    }
}

