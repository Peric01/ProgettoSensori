#include "SensorViewer.h"

SensorViewer::SensorViewer(QWidget* parent) : QWidget (parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File", menuBar);
    QMenu* search = new QMenu("Cerca", menuBar);
    menuBar->addMenu(file);
    menuBar->addMenu(search);

    file->addAction(new QAction("Salva", file));
    file->addAction(new QAction("Apri", file));
    file->addAction(new QAction("Chiudi", file));
    mainLayout->addWidget(menuBar);


    setLayout(mainLayout);
}
