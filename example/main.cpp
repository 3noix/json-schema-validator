#include "qt-json-validator.hpp"
#include <QtDebug>
#include <iostream>
#include <QFile>
#include <QCoreApplication>


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(context)
	
	QByteArray localMsg1 = msg.toLocal8Bit();
	QByteArray localMsg2 = (msg + '\n').toLocal8Bit();
	if (type == QtDebugMsg)
	{
		// sur la sortie standard
		fprintf(stderr, "%s\r\n", localMsg1.constData());
		
		// dans un fichier
		QFile debugFile(QCoreApplication::applicationDirPath() + "/debug.txt");
		debugFile.open(QIODevice::Append);
		debugFile.write(localMsg2.constData());
		debugFile.close();
	}
}


QString readFile(const QString &filePath, bool *ok = nullptr)
{
	QFile file{filePath};
	if (!file.open(QIODevice::ReadOnly)) {
		if (ok) {*ok = false;}
		return {};
	}

	if (ok) {*ok = true;}
	return file.readAll();
}


int main(int argc, char *argv[])
{
	QCoreApplication app{argc, argv};
	qInstallMessageHandler(myMessageOutput);
	QFile debugFile(QCoreApplication::applicationDirPath() + "/debug.txt");
	debugFile.remove();

	const QString personSchema = readFile(":/resources/person.schema.json");
	const QString badPerson = readFile(":/resources/bad-person.json");
	const QString goodPerson = readFile(":/resources/good-person.json");
	const QString goodDefaultedPerson = readFile(":/resources/good-defaulted-person.json");

	qDebug() << "bad person --------------------------------------------------";
	QString error1;
	bool b1 = JsonValidator::validate(personSchema, badPerson, &error1);
	qDebug() << "b = " << b1;
	qDebug() << "error = " << error1;
	qDebug() << "";

	qDebug() << "good person -------------------------------------------------";
	QString error2;
	bool b2 = JsonValidator::validate(personSchema, goodPerson, &error2);
	qDebug() << "b = " << b2;
	qDebug() << "error = " << error2;
	qDebug() << "";

	qDebug() << "good defaulted person ---------------------------------------";
	QString error3;
	bool b3 = JsonValidator::validate(personSchema, goodDefaultedPerson, &error3);
	qDebug() << "b = " << b3;
	qDebug() << "error = " << error3;
	qDebug() << "";

	qDebug() << "Press enter to terminate";
	std::cin.get();
	return EXIT_SUCCESS;
}

