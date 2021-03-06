#pragma once

#include <QMainWindow>
#include <QtWidgets>

#include "stdafx.h"
#include "path.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionReload_triggered();
  void on_actionDisplay_triggered();
  void on_actionSave_triggered();
  void on_actionUpdate_Path_triggered();
  void on_actionVersion_triggered();

  void on_cleanObsolete_clicked();

  bool eventFilter(QObject *object, QEvent *event);

private:
  QString getPath();
  void drawPath();
  void updateTitle();

  std::unique_ptr<Ui::MainWindow> ui;
  std::unique_ptr<Path> path;
};
