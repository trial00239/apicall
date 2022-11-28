#include "./ui_mainwindow.h"
#include "mainwindow.h"

std::vector<std::string> Codes = {"AUD","INR","NPR","CAD","CNY"};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(auto e:Codes){
        ui->comboBox->addItem(QString::fromLocal8Bit(e));
        ui->comboBox_2->addItem(QString::fromLocal8Bit(e));
    }
    ui->Status->setText("No Conversion Done!!");
    makeConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makeConnection(){
    std::string KEY = "7f901f5db2084e6d9f2fdbe72ec3b551";
    std::string URL = "https://api.currencyfreaks.com/latest?apikey=";
    URL+=KEY;
    URL+="&format=json";
    cpr::Response r = cpr::Get(cpr::Url{URL});
    std::cout << "Status code: " << r.status_code << '\n';
    std::string response = r.text;
    std::cout<<response<<endl;
    this->conversionRates = parseString(response);
}

void MainWindow::on_pushButton_clicked(){
    QString inCurr = ui->comboBox->currentText();
    QString outCurr = ui->comboBox_2->currentText();
    QString amount = ui->input->displayText();

    double result = giveConversion(inCurr.toLocal8Bit().constData(),outCurr.toLocal8Bit().constData(),amount.toDouble(),conversionRates);
    std::string s_result = std::to_string(result);
    std::cout<<s_result<<std::endl;
    ui->output->setText(QString::fromLocal8Bit(s_result));
    ui->Status->setText("Conversion Success!!!");
}
void MainWindow::on_pushButton_2_clicked(){
    close();
}

