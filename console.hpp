#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QPalette>

class Console : public QWidget {
  Q_OBJECT

  public:
    explicit Console(QWidget *parent = 0);
    ~Console();
    void log(QString);

  signals:

  public slots:
    void update();

  private:
    QList<QLabel *> list_log;
    QTimer *timer;
    QVBoxLayout *qbl_general;
};

#endif
