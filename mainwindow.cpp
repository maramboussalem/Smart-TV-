#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsors.h"
#include <QtDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlRecord>
#include <QModelIndex>
#include <QTextDocument>
#include <QFileDialog>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPrinter>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QInputDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QTableWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    S() // Initialize Sponsors object
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, 9999999, this));

    // Fetch and populate ID_SPONSOR values into the combo box
    QSqlQueryModel* model = S.afficher();
    for (int i = 0; i < model->rowCount(); ++i) {
        int id = model->record(i).value("ID_SPONSOR").toInt();
        ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
    }
    delete model; // Clean up model
    ui->tableView->setModel(S.afficher());
  connect(ui->stats2, SIGNAL(clicked()), this, SLOT(on_stats2_clicked()));
  statsWidget = new QWidget(this);
      QVBoxLayout *layout = new QVBoxLayout(statsWidget);
      statsWidget->setLayout(layout);

      int ret=A.connect_arduino(); // lancer la connexion à arduino
      switch(ret){
      case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
          break;
      case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
         break;
      case(-1):qDebug() << "arduino is not available";
      }
       QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
       //le slot update_label suite à la reception du signal readyRead (reception des données).
}

void MainWindow::update_label()
{
    // Lire les données de l'Arduino

    data = A.read_from_arduino();
    QString rached = QString::fromUtf8(data);

    if (data == "BuzzerActive")
    {
        QMessageBox::information(this, "warning", "Your heart beat is more than 90 beats.");
    }

    // Vérifier si les données sont lues correctement
    if (data.isEmpty()) {
        ui->labelBPM->setText("Aucune donnée lue depuis Arduino.");
        return;
    }

    // Vérifier si les données reçues sont au format BPM
    if (data.startsWith("BPM: ")) {
        QMessageBox::information(this, "warning", "Your heart beat is more than 90 beats.");

        QString searchText = ui->lineEdit_3->text();
        // Extraire la valeur BPM des données
        QString bpmString = data.mid(5); // 5 est la longueur de "BPM: "
        int BPM = bpmString.toInt(); // Convertir la chaîne en entier

        // Afficher les données BPM dans l'étiquette
        ui->labelBPM->setText("BPM: " + QString::number(BPM));

        // Vérifier si le BPM est supérieur à 90
        if (BPM > 90) {
            // Afficher un message lorsque le BPM dépasse 90
            ui->labelBPM->setText("Heart rate is above 90 BPM!");
        }

        // Faites ce que vous voulez avec la valeur BPM ici
    } else {
        // Afficher les données non reconnues dans l'étiquette
        ui->labelBPM->setText("your heart beat : " + data);
    }
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_ajouter_clicked()
{
    QString id_sponsor_str = ui->lineEdit->text();
    QString num_contrat_str = ui->lineEdit_5->text();

    // Validate ID_SPONSOR
    QIntValidator idValidator(1, 9999999, this);
    int pos = 0;
    if (idValidator.validate(id_sponsor_str, pos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Invalid Input", "ID_SPONSOR must be a positive integer between 1 and 9999999.");
        return;
    }

    // Validate NUM_CONTRAT
    if (idValidator.validate(num_contrat_str, pos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Invalid Input", "NUM_CONTRAT must be a positive integer between 1 and 9999999.");
        return;
    }

    int ID_SPONSOR = id_sponsor_str.toInt();
    int NUM_CONTRAT = num_contrat_str.toInt();
    QString CATEGORY = ui->comboBox_Category->currentText(); // Use current text of combo box
    QString DURE_CONTRAT = ui->lineEdit_2->text();
    QString NOM = ui->lineEdit_4->text();

    Sponsors S(ID_SPONSOR, NUM_CONTRAT, CATEGORY, DURE_CONTRAT, NOM);
    if(S.ajouter())
    {
        qDebug() << "Insertion successful";
        QMessageBox::information(this, "Insertion Successful", "New sponsor has been added successfully.");
         ui->tableView->setModel(S.afficher());
         ui->lineEdit->clear();
         ui->lineEdit_5->clear();
         ui->lineEdit_2->clear();
         ui->lineEdit_4->clear();

        // Update the combo box after insertion
        ui->comboBox_ID_SPONSOR->clear();
        QSqlQueryModel* model = S.afficher();
        for (int i = 0; i < model->rowCount(); ++i) {
            QSqlRecord record = model->record(i);
            int id = record.value("ID_SPONSOR").toInt();
            ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
        }
        delete model; // Clean up model
    }
    else
    {
        qDebug() << "Failed to insert data";
        // Optionally, you can add code here to show an error message.
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_deleteBut_clicked()
{
    int ID_SPONSOR = ui->id_del->text().toInt();
    bool deleted = S.supprimer(ID_SPONSOR);
    if (deleted) {
        qDebug() << "Suppression successful";
       QMessageBox::information(this, "Delete Successful", "Entry with ID_SPONSOR " + QString::number(ID_SPONSOR) + " has been deleted successfully.");
        ui->tableView->setModel(S.afficher());
        // Update the combo box after insertion
               ui->comboBox_ID_SPONSOR->clear();
               QSqlQueryModel* model = S.afficher();
               for (int i = 0; i < model->rowCount(); ++i) {
                   QSqlRecord record = model->record(i);
                   int id = record.value("ID_SPONSOR").toInt();
                   ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
               }
               delete model; // Clean up model

    } else {
        qDebug() << "Failed to delete entry";
        QMessageBox::warning(this, "Delete Entry", "ID_SPONSOR not found in the table");
    }
}

void MainWindow::on_modifyButton_clicked()
{
    int ID_SPONSOR = ui->id_modify_2->text().toInt();

    int newNumContrat = ui->newNumContrat->text().toInt();
    QString newCategory = ui->newCategory->currentText();
    QString newDureContrat = ui->newDureContrat->text();
    QString newNom = ui->newNom->text();

    bool modified = S.modifier(ID_SPONSOR, newNumContrat, newCategory, newDureContrat, newNom);
    if (modified) {
        qDebug() << "Modification successful";
        QMessageBox::information(this, "Modification Successful", "Entry with ID_SPONSOR " + QString::number(ID_SPONSOR) + " has been modified successfully.");

        // Update the combobox contents
        ui->comboBox_ID_SPONSOR->clear();
        QSqlQueryModel* model = S.afficher();
        for (int i = 0; i < model->rowCount(); ++i) {
            int id = model->record(i).value("ID_SPONSOR").toInt();
            ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
        }
        delete model; // Clean up model

        // Update the table view
        ui->tableView->setModel(S.afficher());
    } else {
        qDebug() << "Failed to modify entry";
        QMessageBox::warning(this, "Modification Failed", "Failed to modify entry with ID_SPONSOR " + QString::number(ID_SPONSOR));
    }
}


void MainWindow::on_showButton_clicked()
{
    // Get the selected ID from the combo box
    int selectedID = ui->comboBox_ID_SPONSOR->currentText().toInt();

    // Retrieve sponsor information based on the selected ID
    Sponsors sponsor = S.getSponsorByID(selectedID);

    // Check if the sponsor with the selected ID exists
    if (sponsor.getID_SPONSOR() != 0) {
        // Display sponsor information in the respective line edit widgets
        ui->id_modify_2->setText(QString::number(sponsor.getID_SPONSOR()));
        ui->newNumContrat->setText(QString::number(sponsor.getNUM_CONTRAT()));
        ui->newCategory->setCurrentText(sponsor.getCATEGORY());
        ui->newDureContrat->setText(sponsor.getDURE_CONTRAT());
        ui->newNom->setText(sponsor.getNOM());
    } else {
        // If sponsor with the selected ID does not exist, show a message box
        QMessageBox::warning(this, "ID Not Found", "Sponsor with the selected ID does not exist.");
    }





}

void MainWindow::on_Reset_clicked()
{

    ui->newNumContrat->clear();
    ui->newCategory->clear();
    ui->newDureContrat->clear();
    ui->newNom->clear();
}

void MainWindow::on_Reset_2_clicked()
{

    ui->lineEdit->clear();
    ui->lineEdit_5->clear();
    //ui->lineEdit_9->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
}

void MainWindow::on_ranking_clicked()
{
    ui->tableView->setModel(S.rankingByNumContrat());
}


void MainWindow::on_ranking_2_clicked()
{
    ui->tableView->setModel(S.rankingBycat());
}


/*
int MainWindow::countType(const QString &category) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Sponsors WHERE CATEGORY = ?");
    query.addBindValue(category);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0; // Error occurred or no records found
}

// Function to create a colorful circle chart showing category statistics
void MainWindow::createColorfulCircleChart() {
    // Calculate the count of each category
    int goldCount = countType("gold");
    int silverCount = countType("silver");
    int platinumCount = countType("platinum");
    int bronzeCount = countType("bronze");

    // Create a pie series and add slices for each category

    QPieSeries *series = new QPieSeries();
    series->append("Gold", goldCount);
    series->append("Silver", silverCount);
    series->append("Platinum", platinumCount);
    series->append("Bronze", bronzeCount);

    // Create a chart and set the series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Category Statistics");

    // Create a chart view and set the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the size and style
    chartView->setFixedSize(400, 400);
    chartView->setStyleSheet("background-color: white;");

    // Show the chart
    chartView->show();
}

void MainWindow::on_stats_clicked()
{
    createColorfulCircleChart();
}

void MainWindow::on_colorfulCircleButton_clicked() {
    createColorfulCircleChart();
}*/



void MainWindow::on_stats_2_clicked()
{
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

    if (model) {
        QString content = "<html><head><style>table { margin: auto; }</style></head><body>";

        // Add title
        content += "<h1 style='text-align:center'>STREAMFLIX</h1>";

        // Add table
        content += "<table border='1'>";

        // Add table headers
        content += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            content += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
        }
        content += "</tr>";

        // Add table data
        for (int row = 0; row < model->rowCount(); ++row) {
            content += "<tr>";
            for (int col = 0; col < model->columnCount(); ++col) {
                content += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
            }
            content += "</tr>";
        }

        content += "</table></body></html>";

        QTextDocument document;
        document.setHtml(content);

        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "info", "Fichiers PDF (*.pdf)");

        if (!fileName.isEmpty()) {
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);

            document.print(&printer);

            QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
        }
    }
}



void MainWindow::on_stats_clicked()
{
    // Call the createColorfulCircleChart function using an instance of the Sponsors class
    Sponsors sponsors;
    sponsors.createColorfulCircleChart();

}



void MainWindow::on_ok_clicked()
{
    QString ques1, ques2, ques3, ques4, ques5;

    //ques1
    if (ui->radioButton->isChecked())
        ques1 = ui->radioButton->text();
    else if (ui->radioButton_2->isChecked())
        ques1 = ui->radioButton_2->text();
    else if (ui->radioButton_3->isChecked())
        ques1 = ui->radioButton_3->text();
    else if (ui->radioButton_4->isChecked())
        ques1 = ui->radioButton_4->text();

    //ques2
    if (ui->radioButton_5->isChecked())
        ques2 = ui->radioButton_5->text();
    else if (ui->radioButton_6->isChecked())
        ques2 = ui->radioButton_6->text();
    else if (ui->radioButton_7->isChecked())
        ques2 = ui->radioButton_7->text();


    //ques3
    if (ui->radioButton_12->isChecked())
        ques3 = ui->radioButton_12->text();
    else if (ui->radioButton_9->isChecked())
        ques3 = ui->radioButton_9->text();
    else if (ui->radioButton_10->isChecked())
        ques3 = ui->radioButton_10->text();
    else if (ui->radioButton_11->isChecked())
        ques3 = ui->radioButton_11->text();


    //ques4
    if (ui->radioButton_20->isChecked())
        ques4 = ui->radioButton_20->text();
    else if (ui->radioButton_21->isChecked())
        ques4 = ui->radioButton_21->text();
    else if (ui->radioButton_22->isChecked())
        ques4 = ui->radioButton_22->text();
    else if (ui->radioButton_23->isChecked())
        ques4 = ui->radioButton_23->text();

    //ques5
    if (ui->radioButton_24->isChecked())
        ques5 = ui->radioButton_24->text();
    else if (ui->radioButton_25->isChecked())
        ques5 = ui->radioButton_25->text();
    else if (ui->radioButton_26->isChecked())
        ques5 = ui->radioButton_26->text();
    else if (ui->radioButton_27->isChecked())
        ques5 = ui->radioButton_27->text();

    Sponsors sponsors;
    bool success = sponsors.addQuestions(ques1, ques2, ques3, ques4, ques5);
    if (success) {
        QMessageBox::information(this, "Success", "Questions added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add questions.");
    }
}


void MainWindow::on_stats2_clicked()
{
    // Create an instance of the Sponsors class
    Sponsors sponsors;

    // Clear the layout before adding new charts
    QLayoutItem *child;
    while ((child = statsWidget->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Generate statistics for question 1 and display them
    sponsors.createStatsChart("ques1");

    // Show the widget containing the chart
    statsWidget->show();
}




void MainWindow::on_stats2_2_clicked()
{
    // Create an instance of the Sponsors class
        Sponsors sponsors;

        // Clear the layout before adding new charts
        QLayoutItem *child;
        while ((child = statsWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Generate statistics for question 1 and display them
        sponsors.createStatsChart("ques2");

        // Show the widget containing the chart
        statsWidget->show();
}

void MainWindow::on_stats2_3_clicked()
{
    // Create an instance of the Sponsors class
        Sponsors sponsors;

        // Clear the layout before adding new charts
        QLayoutItem *child;
        while ((child = statsWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Generate statistics for question 1 and display them
        sponsors.createStatsChart("ques3");

        // Show the widget containing the chart
        statsWidget->show();
}

void MainWindow::on_stats2_4_clicked()
{
    // Create an instance of the Sponsors class
        Sponsors sponsors;

        // Clear the layout before adding new charts
        QLayoutItem *child;
        while ((child = statsWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Generate statistics for question 1 and display them
        sponsors.createStatsChart("ques4");

        // Show the widget containing the chart
        statsWidget->show();
}

void MainWindow::on_stats2_5_clicked()
{
    // Create an instance of the Sponsors class
        Sponsors sponsors;

        // Clear the layout before adding new charts
        QLayoutItem *child;
        while ((child = statsWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Generate statistics for question 1 and display them
        sponsors.createStatsChart("ques5");

        // Show the widget containing the chart
        statsWidget->show();
}
/*
void MainWindow::on_logo1_clicked()
{
}
*/

void MainWindow::on_logo1_2_clicked()
{

    // Open a file dialog to select an image file
   // QString fileName = "logo3.png";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.jpg *.bmp)"));

    // Check if a file was selected
    if (!fileName.isEmpty()) {
        // Load the image
        QPixmap image(fileName);

        // Check if the image was loaded successfully
        if (!image.isNull()) {
            // Scale down the image to fit within a reasonable size
            QSize scaledSize(150, 80); // Adjust the dimensions as needed
            image = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // Create a QLabel to display the image
            QLabel *imageLabel = new QLabel(this);

            // Set the image to the QLabel
            imageLabel->setPixmap(image);

            // Set the size policy to Fixed so the label doesn't resize automatically
            imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            // Choose the desired position to place the label
            int xPos = 100; // Adjust the x-coordinate as needed
            int yPos = 100; // Adjust the y-coordinate as needed
            int labelWidth = image.width(); // Use the width of the scaled image
            int labelHeight = image.height(); // Use the height of the scaled image
            imageLabel->setGeometry(xPos, yPos, labelWidth, labelHeight);

            // Show the image label
            imageLabel->show();

            // Create a property animation to animate the position of the image label
            QPropertyAnimation *animation = new QPropertyAnimation(imageLabel, "pos");
            animation->setDuration(1050); // Set the duration of the animation (in milliseconds)
            animation->setLoopCount(-1); // Infinite loop
            animation->setKeyValueAt(0, imageLabel->pos());
            animation->setKeyValueAt(0.5, imageLabel->pos() - QPoint(0, 20)); // Adjust the movement distance as needed
            animation->setKeyValueAt(1, imageLabel->pos());
            animation->setEasingCurve(QEasingCurve::InOutSine); // Use a smooth easing curve

            // Start the animation
            animation->start();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        }
    }
}


void MainWindow::on_logo2_clicked()
{
    // Open a file dialog to select an image file
    QString fileName = "logo3.png";

    // Check if a file was selected
    if (!fileName.isEmpty()) {
        // Load the image
        QPixmap image(fileName);

        // Check if the image was loaded successfully
        if (!image.isNull()) {
            // Scale down the image to fit within a reasonable size
            QSize scaledSize(150, 80); // Adjust the dimensions as needed
            image = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // Create a QLabel to display the image
            QLabel *imageLabel = new QLabel(this);

            // Set the image to the QLabel
            imageLabel->setPixmap(image);

            // Set the size policy to Fixed so the label doesn't resize automatically
            imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            // Adjust the geometry to place the label on the bottom right corner
            int labelWidth = image.width(); // Use the width of the scaled image
            int labelHeight = image.height(); // Use the height of the scaled image
            int windowWidth = this->width(); // Get the width of the main window
            int windowHeight = this->height(); // Get the height of the main window
            imageLabel->setGeometry(windowWidth - labelWidth, windowHeight - labelHeight, labelWidth, labelHeight);

            // Show the image label
            imageLabel->show();

            // Create a property animation to animate the position of the image label
            QPropertyAnimation *animation = new QPropertyAnimation(imageLabel, "pos");
            animation->setDuration(1050); // Set the duration of the animation (in milliseconds)
            animation->setLoopCount(-1); // Infinite loop
            animation->setKeyValueAt(0, imageLabel->pos());
            animation->setKeyValueAt(0.5, imageLabel->pos() + QPoint(0, 20)); // Adjust the movement distance as needed
            animation->setKeyValueAt(1, imageLabel->pos());
            animation->setEasingCurve(QEasingCurve::InOutSine); // Use a smooth easing curve

            // Start the animation
            animation->start();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        }
    }
}





void MainWindow::on_logo2_3_clicked()
{// Open a file dialog to select an image file
    QString fileName = "logo3.png";

    // Check if a file was selected
    if (!fileName.isEmpty()) {
        // Load the image
        QPixmap image(fileName);

        // Check if the image was loaded successfully
        if (!image.isNull()) {
            // Scale down the image to fit within a reasonable size
            QSize scaledSize(150, 80); // Adjust the dimensions as needed
            image = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // Create a QLabel to display the image
            QLabel *imageLabel = new QLabel(this);

            // Set the image to the QLabel
            imageLabel->setPixmap(image);

            // Set the size policy to Fixed so the label doesn't resize automatically
            imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            // Adjust the geometry to place the label on the top right corner
            int labelWidth = image.width(); // Use the width of the scaled image
            int labelHeight = image.height(); // Use the height of the scaled image
            int windowWidth = this->width(); // Get the width of the main window
            imageLabel->setGeometry(windowWidth - labelWidth, 0, labelWidth, labelHeight); // Set y position to 0

            // Show the image label
            imageLabel->show();

            // Create a property animation to animate the position of the image label
            QPropertyAnimation *animation = new QPropertyAnimation(imageLabel, "pos");
            animation->setDuration(1050); // Set the duration of the animation (in milliseconds)
            animation->setLoopCount(-1); // Infinite loop
            animation->setKeyValueAt(0, imageLabel->pos());
            animation->setKeyValueAt(0.5, imageLabel->pos() + QPoint(0, 20)); // Adjust the movement distance as needed
            animation->setKeyValueAt(1, imageLabel->pos());
            animation->setEasingCurve(QEasingCurve::InOutSine); // Use a smooth easing curve

            // Start the animation
            animation->start();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        }
    }
}

void MainWindow::on_logo2_2_clicked()
{
    // Open a file dialog to select an image file
    QString fileName = "logo3.png";

    // Check if a file was selected
    if (!fileName.isEmpty()) {
        // Load the image
        QPixmap image(fileName);

        // Check if the image was loaded successfully
        if (!image.isNull()) {
            // Scale down the image to fit within a reasonable size
            QSize scaledSize(150, 80); // Adjust the dimensions as needed
            image = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // Create a QLabel to display the image
            QLabel *imageLabel = new QLabel(this);

            // Set the image to the QLabel
            imageLabel->setPixmap(image);

            // Set the size policy to Fixed so the label doesn't resize automatically
            imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            // Choose the desired position to place the label
            int xPos = 90; // Adjust the x-coordinate as needed
            int yPos = 550; // Adjust the y-coordinate as needed
            int labelWidth = image.width(); // Use the width of the scaled image
            int labelHeight = image.height(); // Use the height of the scaled image
            imageLabel->setGeometry(xPos, yPos, labelWidth, labelHeight);

            // Show the image label
            imageLabel->show();

            // Create a property animation to animate the position of the image label
            QPropertyAnimation *animation = new QPropertyAnimation(imageLabel, "pos");
            animation->setDuration(1050); // Set the duration of the animation (in milliseconds)
            animation->setLoopCount(-1); // Infinite loop
            animation->setKeyValueAt(0, imageLabel->pos());
            animation->setKeyValueAt(0.5, imageLabel->pos() - QPoint(0, 20)); // Adjust the movement distance as needed
            animation->setKeyValueAt(1, imageLabel->pos());
            animation->setEasingCurve(QEasingCurve::InOutSine); // Use a smooth easing curve

            // Start the animation
            animation->start();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load image."));
        }
    }

}




void MainWindow::on_reset_clicked()
{
    // Iterate through all child widgets
       foreach (QObject *child, this->children()) {
           // Check if the child widget is a QLabel
           QLabel *imageLabel = qobject_cast<QLabel*>(child);
           if (imageLabel) {
               // Remove the QLabel
               delete imageLabel;
           }
       }
}


void MainWindow::askChatbotAboutServices() {
    // Create a custom dialog for chat display
    QDialog *chatDialog = new QDialog(this);
    chatDialog->setWindowTitle("Chatbot");
    chatDialog->setFixedSize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(chatDialog);

    // Add QTextEdit for displaying chat messages
    QTextEdit *chatTextEdit = new QTextEdit(chatDialog);
    chatTextEdit->setReadOnly(true);
    chatTextEdit->setStyleSheet("QTextEdit { color: white; background-color: #34495E; border-radius: 10px; padding: 15px; font-family: 'Montserrat', sans-serif; font-size: 12px; }");
    layout->addWidget(chatTextEdit);

    // Add QLineEdit for user input
    QLineEdit *inputLineEdit = new QLineEdit(chatDialog);
    inputLineEdit->setPlaceholderText("Type your question here...");
    inputLineEdit->setStyleSheet("QLineEdit { background-color: #ECF0F1; border-radius: 10px; padding: 10px; font-family: 'Montserrat', sans-serif; font-size: 12px; }");
    layout->addWidget(inputLineEdit);

    // Add QPushButton for sending the message
    QPushButton *sendButton = new QPushButton("Send", chatDialog);
    sendButton->setStyleSheet("QPushButton { color: white; background-color: #3498DB; border: none; padding: 5px 15px; font-family: 'Montserrat', sans-serif; font-size: 12px; }"
                              "QPushButton:hover { background-color: #2980B9; }");
    layout->addWidget(sendButton);

    // Add a '?' button to display chatbot instructions
    QPushButton *helpButton = new QPushButton("HELP", chatDialog);
    helpButton->setToolTip("Click for topics");
    layout->addWidget(helpButton);

    // Connect the clicked signal of the helpButton to a slot
    connect(helpButton, &QPushButton::clicked, [=]() {
        // Display a message box with the list of topics
        QMessageBox::information(chatDialog, "Topics", "You can ask about:\n- Events\n- Sponsorship\n- Upcoming events\n- Benefits\n- Attending events(attend)\n- Volunteering(volunteer)\n- Industry sector\n- Engagement duration\n- Budget\n- Measure success");
    });

    chatDialog->setLayout(layout);

    // Connect sendButton clicked signal to process the question
    connect(sendButton, &QPushButton::clicked, [=]() {
        QString question = inputLineEdit->text().simplified().toLower(); // Normalize and convert to lowercase

        // Check if the user input is empty
        if (question.isEmpty()) {
            QMessageBox::warning(this, "Empty Question", "Please ask a question for the chatbot.");
            return;
        }

        // Process the user's question and provide an appropriate response
        QString response;
        if (question.indexOf("event", 0, Qt::CaseInsensitive) != -1) {
            response = "Our company hosts a variety of events, including talent shows, game nights, movie screenings, and live performances.";
        } else if (question.indexOf("sponsorship", 0, Qt::CaseInsensitive) != -1) {
            response = "If you are interested in sponsoring our events, please contact our sponsorship team at sponsorships@example.com. They will provide you with more information and discuss sponsorship opportunities.";
        } else if (question.indexOf("upcoming event", 0, Qt::CaseInsensitive) != -1) {
            response = "Yes, we have several upcoming events that are available for sponsorship. You can choose from our list of upcoming talent shows, movie screenings, and charity fundraisers.";
        } else if (question.indexOf("benefit", 0, Qt::CaseInsensitive) != -1) {
            response = "Sponsors receive various benefits, including brand exposure through event marketing, logo placement in promotional materials, VIP access to events, and the opportunity to connect with our audience.";
        } else if (question.indexOf("attend", 0, Qt::CaseInsensitive) != -1) {
            response = "To attend one of our events, you can purchase tickets on our website or at the event venue. Keep an eye on our social media for announcements about upcoming events and ticket sales.";
        } else if (question.indexOf("volunteer", 0, Qt::CaseInsensitive) != -1) {
            response = "Yes, we welcome volunteers at our events! If you are interested in volunteering, please visit our website and fill out the volunteer application form. Our volunteer coordinator will contact you with more details.";
        } else if (question.indexOf("industry sector", 0, Qt::CaseInsensitive) != -1) {
            response = "Our company operates in the IT and technology sector, offering software development services and technology consulting.";
        } else if (question.indexOf("engagement duration", 0, Qt::CaseInsensitive) != -1) {
            response = "The engagement duration depends on your sponsorship needs and goals. We can discuss short-term, medium-term, and long-term sponsorship options to find the best solution for your company.";
        } else if (question.indexOf("budget", 0, Qt::CaseInsensitive) != -1) {
            response = "The budget for sponsorship depends on several factors, including the scope of brand visibility, associated promotional activities, and desired benefits. We can customize a sponsorship package that aligns with your goals and budget.";
        } else if (question.indexOf("measure success", 0, Qt::CaseInsensitive) != -1) {
            response = "We measure sponsorship success by monitoring various indicators, such as increased brand awareness, audience engagement at events, media coverage, and business conversions. We are also open to discussing specific KPIs that are relevant to your company.";
        } else {
            response = "Sorry, I don't have information on that topic. Please ask another question or contact our support team for assistance.";
        }
        chatTextEdit->append(QString("<b>User:</b> %1<br><b>Bot:</b> %2").arg(question).arg(response));
        inputLineEdit->clear();
    });



    // Display the chat dialog
    chatDialog->exec();
}





void MainWindow::on_reset_2_clicked()
{
     askChatbotAboutServices();
}
/*
void MainWindow::on_recherche_activated(const QString &text)
{

}*/

void MainWindow::recherche(const QString& searchText) {
    // Get the model associated with the QTableView
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) return; // Check if the model exists

    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    // Loop through each row in the table
    for (int row = 0; row < rowCount; ++row) {
        bool found = false;
        // Loop through each column in the table
        for (int col = 0; col < columnCount; ++col) {
            // Get the index for the current cell
            QModelIndex index = model->index(row, col);
            QString cellText = index.data().toString();
            // Check if the cell text contains the search text
            if (cellText.contains(searchText, Qt::CaseInsensitive)) {
                found = true;

                break; // No need to check other columns in this row
            }
        }
        // If the search text is found in any column of the current row, make the row visible
        ui->tableView->setRowHidden(row, !found);
    }
}


void MainWindow::on_find_clicked() {
    QString searchText = ui->lineEdit_3->text(); // Assuming your line edit object name is "lineEdit"
    recherche(searchText);

}


void MainWindow::on_reset_search_clicked()
{
    // Clear the search line edit
       ui->lineEdit_3->clear();

       // Get the model associated with the QTableView
       QAbstractItemModel *model = ui->tableView->model();
       if (!model) return; // Check if the model exists

       int rowCount = model->rowCount();

       // Loop through each row in the table and make them all visible
       for (int row = 0; row < rowCount; ++row) {
           ui->tableView->setRowHidden(row, false);
       }
}

void MainWindow::on_pushButton_4_clicked()
{
    A.write_to_arduino("1");
}
