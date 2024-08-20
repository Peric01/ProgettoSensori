#include "SensorViewer.h"

void SensorViewer::addMenus(QVBoxLayout* mainLayout)
{
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File", menuBar);
    menuBar->addMenu(file);
    QMenu* NewSensor = new QMenu("Aggiungi Sensore", menuBar);
    menuBar->addMenu(NewSensor);

    // Menu/Gestione File
    file->addAction(new QAction("Salva", file));
    file->addAction(new QAction("Apri", file));
    file->addAction(new QAction("Chiudi", file));
    // Menu/Aggiunta Sensori
    NewSensor->addAction(new QAction("Temperatura", NewSensor));
    NewSensor->addAction(new QAction("Torbidità", NewSensor));
    NewSensor->addAction(new QAction("PH", NewSensor));

    mainLayout->addWidget(menuBar);

    // Menu/Barra di ricerca nel Menu
    QLineEdit* searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");
    menuBar->setCornerWidget(searchBar);
}

void SensorViewer::addSensors(QVBoxLayout* sensorLayout)
{
    QLabel* temperatureLabel = new QLabel("Temperature Sensors", this);
    QVBoxLayout* temperatureLayout = new QVBoxLayout;
    temperatureLayout->addWidget(temperatureLabel);

    // Aggiungi i sensori di temperatura (puoi aggiungere dinamicamente)
    for (int i = 1; i <= 10; i++) { // Esempio con 10 sensori
        temperatureLayout->addWidget(new QLabel("Temperature Sensor " + QString::number(i), this));
    }

    // Scroll area per i sensori di temperatura
    QScrollArea* temperatureScrollArea = new QScrollArea(this);
    QWidget* temperatureWidget = new QWidget();
    temperatureWidget->setLayout(temperatureLayout);
    temperatureScrollArea->setWidget(temperatureWidget);
    temperatureScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(temperatureScrollArea);

    // Sezione per i sensori di torbidità
    QLabel* turbidityLabel = new QLabel("Turbidity Sensors", this);
    QVBoxLayout* turbidityLayout = new QVBoxLayout;
    turbidityLayout->addWidget(turbidityLabel);

    // Aggiungi i sensori di torbidità
    for (int i = 1; i <= 8; i++) { // Esempio con 8 sensori
        turbidityLayout->addWidget(new QLabel("Turbidity Sensor " + QString::number(i), this));
    }

    // Scroll area per i sensori di torbidità
    QScrollArea* turbidityScrollArea = new QScrollArea(this);
    QWidget* turbidityWidget = new QWidget();
    turbidityWidget->setLayout(turbidityLayout);
    turbidityScrollArea->setWidget(turbidityWidget);
    turbidityScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(turbidityScrollArea);

    // Sezione per i sensori di pH
    QLabel* phLabel = new QLabel("pH Sensors", this);
    QVBoxLayout* phLayout = new QVBoxLayout;
    phLayout->addWidget(phLabel);

    // Aggiungi i sensori di pH
    for (int i = 1; i <= 5; i++) { // Esempio con 5 sensori
        phLayout->addWidget(new QLabel("pH Sensor " + QString::number(i), this));
    }

    // Scroll area per i sensori di pH
    QScrollArea* phScrollArea = new QScrollArea(this);
    QWidget* phWidget = new QWidget();
    phWidget->setLayout(phLayout);
    phScrollArea->setWidget(phWidget);
    phScrollArea->setWidgetResizable(true);
    sensorLayout->addWidget(phScrollArea);
}

void SensorViewer::addData(QHBoxLayout* dataLayout)
{
    QLabel* staticDataLabel = new QLabel("Dati Statici", this);
    QLabel* editableDataLabel = new QLabel("Dati Modificabili", this);
    dataLayout->addWidget(staticDataLabel);
    dataLayout->addWidget(editableDataLabel);
}

void SensorViewer::addButtons(QVBoxLayout* buttonLayout)
{
    QPushButton* saveButton = new QPushButton("Salva", this);
    QPushButton* modifyButton = new QPushButton("Modifica", this);
    QPushButton* deleteButton = new QPushButton("Elimina", this);
    QPushButton* runSimulationButton = new QPushButton("Lancia Simulazione", this);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(deleteButton);
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

void SensorViewer::showSensor(Sensor* s){
    // diviso in due parti destra e sinistra per dati statici e dati dinamici
    // bisogna poi metterlo in data and buttons in sensorviewer
    QHBoxLayout* Data = new QHBoxLayout;

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
    addData(showSensor());
    addButtons(buttonLayout);

    dataAndButtonsLayout->addLayout(buttonLayout); // Aggiungi i pulsanti a destra dei dati

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


