#include "SensorViewer.h"

SensorViewer::SensorViewer(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    // Menu
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File", menuBar);
    menuBar->addMenu(file);

    // Menu/Gestione File
    file->addAction(new QAction("Salva", file));
    file->addAction(new QAction("Apri", file));
    file->addAction(new QAction("Chiudi", file));
    mainLayout->addWidget(menuBar);

    // Menu/Barra di ricerca nel Menu
    QLineEdit* searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    menuBar->setCornerWidget(searchBar);

    // Layout principale con due colonne: sinistra (sensori) e destra (dati e grafico)
    QHBoxLayout* screenLayout = new QHBoxLayout;

    // Colonna sinistra: Elenco dei sensori
    QVBoxLayout* sensorLayout = new QVBoxLayout;
    QFrame* sensorFrame = new QFrame(this);
    sensorFrame->setFrameStyle(QFrame::Box);
    sensorFrame->setStyleSheet("border: 2px solid black;");  // Bordo esterno nero
    sensorFrame->setLayout(sensorLayout);

    // Esempio di aggiunta di sensori alla lista (puoi aggiungere dinamicamente)
    QLabel* sensorLabel1 = new QLabel("Torbidity", this);
    QLabel* sensorLabel2 = new QLabel("Temperature", this);
    QLabel* sensorLabel3 = new QLabel("PH", this);

    sensorLayout->addWidget(sensorLabel1);
    sensorLayout->addWidget(sensorLabel2);
    sensorLayout->addWidget(sensorLabel3);
    sensorLayout->addStretch();

    // Colonna destra: Divisa in due righe (dati e pulsanti sopra, grafico sotto)
    QVBoxLayout* dataAndGraphLayout = new QVBoxLayout;

    // Parte superiore: Dati statici, modificabili, e pulsanti in orizzontale
    QHBoxLayout* dataLayout = new QHBoxLayout;

    // Aggiungi widget per i dati (statici e modificabili)
    QLabel* staticDataLabel = new QLabel("Dati Statici", this);
    QLabel* editableDataLabel = new QLabel("Dati Modificabili", this);
    dataLayout->addWidget(staticDataLabel);
    dataLayout->addWidget(editableDataLabel);

    // Layout verticale per i pulsanti
    QVBoxLayout* buttonLayout = new QVBoxLayout;

    // Spaziatori per centrare i pulsanti verticalmente
    QSpacerItem* spacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* spacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    buttonLayout->addItem(spacerTop);

    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* modifyButton = new QPushButton("Modify", this);
    QPushButton* deleteButton = new QPushButton("Delete", this);
    QPushButton* runSimulationButton = new QPushButton("Run Simulation", this);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(runSimulationButton);

    buttonLayout->addItem(spacerBottom);

    // Aggiungi i pulsanti alla parte dati
    dataLayout->addLayout(buttonLayout);

    // Parte inferiore: Grafico della simulazione
    QFrame* graphFrame = new QFrame(this);
    graphFrame->setFrameStyle(QFrame::Box);
    graphFrame->setStyleSheet("border: 2px solid black;");  // Bordo esterno nero
    QVBoxLayout* graphLayout = new QVBoxLayout;
    QLabel* graphLabel = new QLabel("Simulazione di grafico dei valori del sensore", this);
    graphFrame->setLayout(graphLayout);
    graphLayout->addWidget(graphLabel);

    // Aggiungi i layout alla colonna destra
    dataAndGraphLayout->addLayout(dataLayout, 1);  // Parte superiore con dati e pulsanti, occupa 50% dello spazio
    dataAndGraphLayout->addWidget(graphFrame, 1);  // Parte inferiore con il grafico, occupa 50% dello spazio

    // Aggiungi la colonna sinistra e destra al layout principale
    screenLayout->addWidget(sensorFrame, 1);  // 1/3 della larghezza per i sensori
    screenLayout->addLayout(dataAndGraphLayout, 2);  // 2/3 della larghezza per i dati e il grafico

    // Aggiungi il layout dello schermo al layout principale
    mainLayout->addLayout(screenLayout);
    setLayout(mainLayout);
}
