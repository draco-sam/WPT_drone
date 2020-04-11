#include <QCoreApplication>//class provides an event loop for Qt applications without UI.
#include <QDebug>
#include <QFile>
#include <QString>

QString get_string(unsigned short i_table);

int main(int argc, char *argv[])
{

    //QApplication    app(argc, argv);
    QCoreApplication a(argc,argv);

    qDebug()<<"bonjour";


    QFile file_2("../QFile_csv/test_sam.txt");

    if (!file_2.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"!!! Impossible d'ouvrir le fichier";
        return 1;
    }

    QTextStream out (&file_2);
    QString texte_out = "ecriture test";

    out<<texte_out;
    file_2.flush();
    file_2.close();


    QString data_str = "";

    data_str = get_string(1015);


    return 0;

    return a.exec();

}//End of main.
//__________________________________________________________________________________________________

QString get_string(unsigned short i_num){
/*
 */
    QString         data_string = "";
    unsigned short  coma        = 0;
    unsigned short  i_table     = i_num - 1000;//offset = 1000.
    QFile file("../QFile_csv/temp.csv");

    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"!!! Impossible d'ouvrir le fichier";
        return "file not readable";
    }

    QTextStream text_stream_in (&file);
    QString     text = text_stream_in.readAll();

    qDebug()<<".csv entier"<<text;

    for(int i=0;i < text.size(); i++){
        if(text[i] == ';'){
            coma++;
        }
        else if(text[i] != '\n' & coma == i_table){
            data_string.append(text[i]);
        }
    }

    file.close();

    qDebug()<<data_string;

    return data_string;

}
