#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    path = std::make_unique<Path>();
    this->DrawPath();
}

void MainWindow::DrawPath() {
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
    auto btnAdd = new QPushButton("Add");
    auto editAdd = new QLineEdit();
    this->ui->formLayout->addRow(btnAdd, editAdd);
}

MainWindow::~MainWindow() { }

void MainWindow::on_actionReload_triggered() {
    path->Reload();
    while (QLayoutItem* item = this->ui->formLayout->takeAt(0)) {
        if (QWidget* widget = item->widget())
            delete widget;
    }
    this->DrawPath();
}

void MainWindow::on_actionDisplay_triggered() {
    QString con;
    for (QLineEdit* qle : this->findChildren<QLineEdit *>()) {
        con += qle->text() + ";";
    }
    auto window = new QDialog(this);
    auto layout = new QVBoxLayout();
    auto btn_Ok = new QPushButton("Ok");
    layout->addWidget(new QTextEdit(con));
    layout->addWidget(btn_Ok);
    connect(btn_Ok, &QPushButton::clicked, [window] () {
         if (window) window->close();
    });
    window->setLayout(layout);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
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
