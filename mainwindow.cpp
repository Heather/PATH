#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->ui->setupUi(this);
  this->ui->findEdit->installEventFilter(this);
  path = std::make_unique<Path>();
  this->drawPath();
}

void MainWindow::updateTitle() {
  QString con = getPath();
  QString title = QString(Path::version.c_str())
     + " [lenght: " + QString::number(con.count()) + "]";
  this->setWindowTitle(title);
}

void MainWindow::drawPath() {
  for (std::string str : path->GetPath()) {
    auto editForm = new QLineEdit();
    auto btnDelete = new QPushButton("Del");
    connect(btnDelete, &QPushButton::clicked, [editForm, btnDelete] () {
      if (editForm) delete editForm;
      if (btnDelete) delete btnDelete;
    });
    QString qstr = QString::fromUtf8(str.c_str());
    editForm->setText(qstr);
    this->ui->formLayout->addRow(btnDelete, editForm);
  }
  auto editAdd = new QLineEdit();
  auto btnAdd = new QPushButton("Add");
  connect(btnAdd, &QPushButton::clicked, [btnAdd, editAdd, this] () {
    auto editForm2 = new QLineEdit(editAdd->text());
    auto btnDelete2 = new QPushButton("Del");
    connect(btnDelete2, &QPushButton::clicked, [editForm2, btnDelete2] () {
      if (editForm2) delete editForm2;
      if (btnDelete2) delete btnDelete2;
    });
    this->ui->formLayout->insertRow(this->ui->formLayout->rowCount() - 1
                                    , btnDelete2, editForm2);
    editAdd->setText("");
  });
  this->ui->formLayout->addRow(btnAdd, editAdd);
  this->updateTitle();
}

MainWindow::~MainWindow() { }

QString MainWindow::getPath() {
  QString con = "";
  for (QLineEdit* qle : this->findChildren<QLineEdit *>()) {
    con += qle->text() + ";";
  }
  return con;
}

void MainWindow::on_actionReload_triggered() {
  path->Reload();
  while (QLayoutItem* item = this->ui->formLayout->takeAt(0)) {
    if (QWidget* widget = item->widget())
      delete widget;
  }
  this->drawPath();
  this->updateTitle();
}

void MainWindow::on_actionDisplay_triggered() {
  QString con = getPath();
  auto window = new QDialog(this);
  auto layout = new QVBoxLayout();
  auto btn_Ok = new QPushButton("Ok");
  layout->addWidget(new QTextEdit(con));
  layout->addWidget(btn_Ok);
  connect(btn_Ok, &QPushButton::clicked, [window] () {
    if (window) window->close();
  });
  window->setLayout(layout);
  window->setAttribute(Qt::WA_DeleteOnClose, true);
  window->show();
  this->updateTitle();
}

void MainWindow::on_actionSave_triggered() {
  auto filename = QFileDialog::getSaveFileName(this, "Save file", "", ".txt");
  if (!filename.contains('.')) filename.append(".txt");
  QFile f( filename );
  f.open( QIODevice::WriteOnly );
  QString con = getPath();
  QTextStream outStream(&f);
  outStream << con;
  f.close();
  this->updateTitle();
}

void MainWindow::on_actionVersion_triggered() {
  auto window = new QDialog(this);
  auto layout = new QVBoxLayout();
  auto btn_Ok = new QPushButton("Ok");
  layout->addWidget(new QLabel(Path::version.c_str()));
  layout->addWidget(btn_Ok);
  connect(btn_Ok, &QPushButton::clicked, [window] () {
    if (window) window->close();
  });
  window->setLayout(layout);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
  if (object == this->ui->findEdit && event->type() == QEvent::KeyPress) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(event);
    if(ke->key()==Qt::Key_Return) {
      QString textToFind = this->ui->findEdit->toPlainText().toUpper();
      for (QLineEdit* qle : this->findChildren<QLineEdit *>()) {
        if (qle->text().toUpper().contains(textToFind)) {
          this->ui->scrollArea->ensureWidgetVisible(qle);
          qle->setFocus();
          return true;
        }
      }
      return true;
    }
    this->updateTitle();
    return false;
  }
  else return false;
}
