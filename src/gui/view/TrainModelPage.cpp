#include "src/gui/view/mainwindow.h"

#include <iomanip>
#include <QValueAxis>

#include "ui_mainwindow.h"

bool MainWindow::exitFromTrainPage() {
	if (this->training_thread != nullptr && this->training_thread->isRunning()) {
		QMessageBox training_is_running_message;
		training_is_running_message.setText(
				"If you stop the learning process, "
				"the progress will not be saved. "
				"Are you sure you want to stop?");
		training_is_running_message.setWindowTitle(
				tr("The training is already running"));
		training_is_running_message.setStandardButtons(
				QMessageBox::Yes | QMessageBox::Cancel);
		training_is_running_message.setDefaultButton(QMessageBox::Cancel);
		int ret = training_is_running_message.exec();
		if (ret == QMessageBox::Yes) {
			this->training_worker->stopTraining();
			this->training_thread->quit();
			this->training_thread->wait();
			delete this->training_thread;
			this->training_thread = nullptr;
		} else
			return false;
	}
	if (this->training_dataset_file != nullptr) {
		delete this->training_dataset_file;
		this->training_dataset_file = nullptr;
	}
	ui->training_progress_bar->hide();
	ui->training_progress_bar->setValue(0);
	ui->chart_widget->hide();
	ui->train_info_text_label->setDisabled(true);
	ui->start_training_push_button->show();
	ui->start_training_push_button->setDisabled(true);
	ui->import_train_dataset_label->clear();
	ui->import_train_dataset_label->setText(
			"<html><head/><body><p><span style=\" "
			"font-size:14pt;\">Drag and drop train dataset file"
			"</span></p><p><span style=\" font-size:14pt;\">"
			" (should be *.csv)</span></p></body></html>");
	ui->file_path_label_2->clear();
	return true;
}

void MainWindow::on_test_model_push_button_2_pressed()
{
	if (exitFromTrainPage())
		ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_to_configure_push_button_pressed()
{
	if (exitFromTrainPage())
		ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::trainDatasetFileWasUploaded(QFile *file)
{
	if (!file->fileName().endsWith(".csv")) {
		QMessageBox::information(this, tr("Wrong file format"),
								 "Incorrect file format. The file must have the .csv extension ");
	} else {
		if (this->training_dataset_file != nullptr) {
			delete this->training_dataset_file;
			this->training_dataset_file = nullptr;
		}
		this->training_dataset_file = file;
		ui->start_training_push_button->setEnabled(true);
		ui->file_path_label_2->setText(file->fileName());
		ui->import_train_dataset_label->setPixmap(
				QPixmap(":/img/empty_file.png").scaled(150, 150));
		ui->start_training_push_button->setEnabled(true);
	}
}

void MainWindow::onTrainingDatasetWasUploaded()
{
	trainDatasetFileWasUploaded(ui->import_train_dataset_label->getUploadedFile());
}

void MainWindow::on_toolButton_3_pressed()
{
	QString file_path =
			QFileDialog::getOpenFileName(this, "Get Any File");
	QDir d = QFileInfo(file_path).absoluteFilePath();
	QFile *file = new QFile(d.absolutePath());
	if (!file->open(QIODevice::ReadOnly)) {
		QMessageBox::information(this,
								 tr("Unable to open file"),
								 file->errorString());
		return;
	} else {
		trainDatasetFileWasUploaded(file);
	}
}

void MainWindow::on_start_training_push_button_pressed()
{
	if (this->training_thread != nullptr && this->training_thread->isRunning()) {
		QMessageBox::information(this,
								 tr("The training is already running"),
								 "Can't start training twice");
		return;
	}
	ui->training_progress_bar->show();
	ui->start_training_push_button->hide();
	this->training_thread = new QThread();
	this->training_worker = new ModelTrainWorker();
	training_worker->setModel(current_model);
	training_worker->setNumOfEpochs(ui->num_of_epochs_spin_box->value());
	training_worker->setDatasetFileName(
			this->training_dataset_file->fileName().toStdString());
	training_worker->moveToThread(this->training_thread);

	connect(this->training_thread, SIGNAL(started()),
			training_worker, SLOT(process()));
	connect(training_worker, SIGNAL(finished()),
			this->training_thread, SLOT(quit()));
	connect(training_worker, SIGNAL(statusChanged(int, int, float)),
			this, SLOT(update_training_status(int, int, float)));
	connect(training_worker, SIGNAL(finished()),
			training_worker, SLOT(deleteLater()));
	connect(this->training_thread, SIGNAL(finished()),
			this->training_thread, SLOT(deleteLater()));

	this->training_thread->start();

	if (!ui->chart_widget->chart()->axes(Qt::Horizontal).isEmpty())
		ui->chart_widget->chart()->removeAxis(ui->chart_widget->chart()->axes(Qt::Horizontal).first());
	auto *x = new QValueAxis();
	x->setMax(ui->num_of_epochs_spin_box->value());
	x->setMin(1);
	ui->chart_widget->chart()->addAxis(x, Qt::AlignBottom);
	chart_series->attachAxis(x);
	this->chart_series->clear();
	ui->chart_widget->show();
}

void MainWindow::update_training_status(int epoch, int completion, float accuracy) {
	ui->train_info_text_label->setEnabled(true);
	std::stringstream ss;
	ss << "<html><head/><body><p><span style=\" font-size:14pt;"
		  " font-weight:700;\">Epoch: </span><span style=\" font-size:14pt;\">"
	   << epoch
	   << "</span></p><p><span style=\" font-size:14pt;"
		  " font-weight:700;\">Current accuracy: </span><span style=\""
		  " font-size:14pt;\">"
	   << std::setprecision(3)
	   << (std::isnan(accuracy) ? 0 : accuracy) << "%"
	   << "</span></p><p><span style=\" font-size:14pt;"
		  " font-weight:700;\">Completion: </span><span style=\""
		  " font-size:14pt;\">"
	   << completion << "%"
	   << "</span></p></body></html>";
	ui->train_info_text_label->setText(ss.str().data());
	ui->training_progress_bar->setValue(completion);
	this->chart_series->append(epoch, accuracy);
	std::cerr << epoch << " " << accuracy << std::endl;
	std::cerr << chart_series->chart() << std::endl;
	setUpdatesEnabled(this->chart_series);
	if (ui->training_progress_bar->value() == 100) {
		ui->test_model_push_button_2->setEnabled(true);
		this->training_thread->quit();
		this->training_thread->wait();
		delete training_thread;
		training_thread = nullptr;
	}
}

