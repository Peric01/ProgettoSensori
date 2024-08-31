#include "SensorViewer.h"
#include "TempSensor.h"
#include "TurbSensor.h"
#include "PHSensor.h"
#include "Controller.h"
#include <QInputDialog>
#include <QPalette>
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>


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

QFrame* SensorViewer::createGrayFrame() {
    QFrame* grayFrame = new QFrame(this);
    grayFrame->setFrameStyle(QFrame::Box);
    grayFrame->setStyleSheet("background-color: gray;");

    QVBoxLayout* layout = new QVBoxLayout;
    grayFrame->setLayout(layout);

    return grayFrame;
}

void SensorViewer::showSensor(Sensor* s) {
    clearLayout(staticBox);
    clearLayout(editableBox);

    QString min = s->isEmpty() ? "N/a" : QString::number(s->getMin());
    QString max = s->isEmpty() ? "N/a" : QString::number(s->getMax());
    QString cur = s->isEmpty() ? "N/a" : QString::number(s->getCurrentValue());

    QLabel* nameLabel = new QLabel("Nome: " + QString::fromStdString(s->getName()), this);
    QLabel* idLabel = new QLabel("ID: " + QString::number(s->getID()), this);
    QLabel* minValueLabel = new QLabel("Valore Minimo: " + min, this);
    QLabel* maxValueLabel = new QLabel("Valore Massimo: " + max, this);
    QLabel* currentValueLabel = new QLabel("Valore Corrente: " + cur, this);

    staticBox->addWidget(nameLabel);
    staticBox->addWidget(idLabel);

    editableBox->addWidget(minValueLabel);
    editableBox->addWidget(maxValueLabel);
    editableBox->addWidget(currentValueLabel);

    QString type = "Tipo: ";
    if (dynamic_cast<TempSensor*>(s)) {
        type += "Temperatura";
    } else if (dynamic_cast<TurbSensor*>(s)) {
        type += "Torbidità";
    } else if (dynamic_cast<PHSensor*>(s)) {
        type += "pH";
    }

    QLabel* typeLabel = new QLabel(type, this);
    staticBox->addWidget(typeLabel);

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
    selectAction = new QAction("Cerca e seleziona", NewSensor);
    NewSensor->addAction(addAction);
    NewSensor->addAction(deleteAction);
    NewSensor->addAction(selectAction);

    mainLayout->addWidget(menuBar);

    /*    // Menu/Barra di ricerca nel Menu
    QLineEdit* searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");
    menuBar->setCornerWidget(searchBar);
    //implementabile in futuro per filtrare i sensori
*/
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
        label->setMaximumHeight(20);
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

    QScrollArea* temperatureScrollArea = new QScrollArea(this);
    QWidget* temperatureWidget = new QWidget();
    temperatureWidget->setLayout(temperatureLayout);
    temperatureScrollArea->setWidget(temperatureWidget);
    temperatureScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(temperatureScrollArea);

    turbidityLayout = new QVBoxLayout;
    turbidityLayout->setAlignment(Qt::AlignTop);

    QLabel* turbidityLabel = new QLabel("Turbidity Sensors", this);
    turbidityLayout->addWidget(turbidityLabel);
    turbidityLabel->setMaximumHeight(20);


    QScrollArea* turbidityScrollArea = new QScrollArea(this);
    QWidget* turbidityWidget = new QWidget();
    turbidityWidget->setLayout(turbidityLayout);
    turbidityScrollArea->setWidget(turbidityWidget);
    turbidityScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(turbidityScrollArea);

    phLayout = new QVBoxLayout;
    phLayout->setAlignment(Qt::AlignTop);

    QLabel* phLabel = new QLabel("pH Sensors", this);
    phLayout->addWidget(phLabel);
    phLabel->setMaximumHeight(20);

    QScrollArea* phScrollArea = new QScrollArea(this);
    QWidget* phWidget = new QWidget();
    phWidget->setLayout(phLayout);
    phScrollArea->setWidget(phWidget);
    phScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(phScrollArea);
}

void SensorViewer::clearData() {
    if (staticBox) {
        clearLayout(staticBox);

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
    staticBox = new QVBoxLayout;
    editableBox = new QVBoxLayout;

    clearData();

    QFrame* staticFrame = new QFrame(this);
    staticFrame->setLayout(staticBox);
    staticFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    staticFrame->setStyleSheet("border: 1px solid black;");

    QFrame* editableFrame = new QFrame(this);
    editableFrame->setLayout(editableBox);
    editableFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    editableFrame->setStyleSheet("border: 1px solid black;");

    dataLayout->addWidget(staticFrame);
    dataLayout->addWidget(editableFrame);
}

void SensorViewer::addButtons(QVBoxLayout* buttonLayout)
{
    addValueButton = new QPushButton("Aggiungi un valore", this);
    removeLastValueButton = new QPushButton("Rimuovi l'ultimo valore", this);

    QHBoxLayout* simulationButtonsLayout = new QHBoxLayout;

    runSimulationButton = new QPushButton("Nuova Simulazione", this);
    runRandomSimulationButton = new QPushButton("Simulazione Random", this);

    simulationButtonsLayout->addWidget(runSimulationButton);
    simulationButtonsLayout->addWidget(runRandomSimulationButton);

    buttonLayout->addWidget(addValueButton);
    buttonLayout->addWidget(removeLastValueButton);

    buttonLayout->addLayout(simulationButtonsLayout);
}

SensorViewer::SensorViewer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* screenLayout = new QHBoxLayout;

    QVBoxLayout* sensorLayout = new QVBoxLayout;
    QFrame* sensorFrame = new QFrame(this);
    sensorFrame->setFrameStyle(QFrame::Box);
    sensorFrame->setStyleSheet("border: 2px solid black;");
    sensorFrame->setLayout(sensorLayout);

    dataAndGraphLayout = new QVBoxLayout;

    QHBoxLayout* dataAndButtonsLayout = new QHBoxLayout;

    graphLayout = new QVBoxLayout;

    QVBoxLayout* buttonLayout = new QVBoxLayout;

    // Menu
    addMenus(mainLayout);

    // Sezione per i sensori
    addSensors(sensorLayout);

    // Aggiunge i dati e i pulsanti
    addData(dataAndButtonsLayout);
    addButtons(buttonLayout);
    dataAndButtonsLayout->addLayout(buttonLayout);

    graphLayout->addWidget(createGrayFrame());
    dataAndGraphLayout->addLayout(dataAndButtonsLayout, 1);
    dataAndGraphLayout->addLayout(graphLayout, 1);

    screenLayout->addWidget(sensorFrame, 1);
    screenLayout->addLayout(dataAndGraphLayout, 2);

    mainLayout->addLayout(screenLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    setMinimumWidth(800);
    setMinimumHeight(400);
    resize(QSize(1024, 720));
}

void SensorViewer::showGraph(QChart* chart) {
    clearLayout(graphLayout);
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    graphLayout->addWidget(chartView);
    graphLayout->update();
}

void SensorViewer::clearGraph(){
    clearLayout(graphLayout);
    graphLayout->addWidget(createGrayFrame());
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
    connect(runRandomSimulationButton, SIGNAL(clicked(bool)), controller, SLOT(randSimulation()));
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
    float value = static_cast<float>(QInputDialog::getDouble(this, tr("Aggiungi Valore"), tr("Inserisci il nuovo valore del sensore:"),1.0, -500.0,4000.0,2,&ok));
    if (ok) {
        return value;
    } else {
        throw std::runtime_error("Selezione annullata");
    }
}

unsigned int SensorViewer::showSearchDialog() {
    bool ok;
    unsigned int sensorId = QInputDialog::getInt(this, tr("Cerca Sensore"),
                                                 tr("Inserisci l'ID del sensore:"), 1, 0, 100, 1, &ok);
    if (ok) {
        return sensorId;
    } else {
        throw std::runtime_error("Ricerca annullata");
    }
}

