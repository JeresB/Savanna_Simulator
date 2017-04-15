#include "console.hpp"

Console::Console(QWidget *parent) : QWidget(parent) {
  this->setMinimumSize(800, 400);

  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);
  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::black);
  this->setAutoFillBackground(true);
  this->setPalette(pal);

  qbl_general = new QVBoxLayout;
  qbl_general->setAlignment(Qt::AlignTop);
  // Création du widget principale
  this->setLayout(qbl_general);

  // QLabel *temp_label = new QLabel("Console", this);
  // list_log.append(temp_label);
}

Console::~Console(){}

void Console::log(QString predator_log) {
  QPalette textColor = QPalette();
	textColor.setColor(QPalette::WindowText,Qt::white);

  QLabel *temp_label = new QLabel(predator_log, this);
  temp_label->setPalette(textColor);
  list_log.append(temp_label);

  qDebug() << "methode log";
  qbl_general->addWidget(temp_label);

}

void Console::update() {

}
