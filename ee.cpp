//mainwindow.h
//void on_locationButton_event_clicked();
//mainwindow.h #
//include <QPainter>
//#include <QUrl>
//#include <QDesktopServices>
//#include <QSqlQuery>
//#include <QSqlError>
//void MainWindow::on_locationButton_event_clicked()
//{ // Get the ID from lineEdit_localisation_event
//    int id_e = ui->lineEdit_localisation_event->text().toInt();
//    // Connect to the database
//    QSqlDatabase db = QSqlDatabase::database();
//    if (!db.isOpen()) { QMessageBox::critical(this, "Database Error", "Connection to the database failed."); return; }
//    // Prepare the query to retrieve the address (lieu) for the given ID from the database
//    QSqlQuery query(db); query.prepare("SELECT lieu FROM GS_EVENEMENT WHERE id_e = :id"); query.bindValue(":id", id_e);
//    // Execute the query
//    if (!query.exec()) { QMessageBox::critical(this, "Query Error", "Failed to execute the query."); return; }
//    // Check if the event with the given ID exists
//    if (!query.next()) { QMessageBox::warning(this, "Event Not Found", "Event with ID " + QString::number(id_e) + " not found."); return; } // Retrieve the address (lieu) from the query result QString address = query.value(0).toString(); // Construct the Google Maps URL using the address QString googleMapsUrl = QString("https://www.google.com/maps/search/?api=1&query=%1").arg(address); // Open the URL in the default web browser QDesktopServices::openUrl(QUrl(googleMapsUrl)); }
