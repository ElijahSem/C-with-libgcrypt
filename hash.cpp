#include "hash.hpp"
#include <fstream>

using namespace std;
Hash::Hash()
{
}

bool Hash::Open(){

    //     Создание дескриптора контекста:
    //     1) C помощью флага GCRY_MD_FLAG_HMAC мы пропускаем наше сообщение через алгоритм MAC
    //     2) С помощью флага GCRY_MD_FLAG_SECURE злоумышленнику будет сложно скопировать данные из оперативной памяти т.к.
    //     мы все буферы выделяются в защищенной памяти ("secure memory")

    gcry_error_t E = gcry_md_open (&hd,GCRY_MD_STRIBOG512, 0);

    return E == 0;
}

void Hash::Close(){

    //Вызываем ф-цию  закрытия дескриптора контекста.
    gcry_md_close (hd);

}

QString Hash::hashing(QString File_name, QProgressBar *loading){

    gcry_md_reset(hd);

    const int N = 2097152; // 2Mb

    // Буфер для открытого текста
    char buffer[N];


    ifstream fin(File_name.toStdString());

    if(!fin) return "";

    while(fin.read(buffer,N)){

        //Ф-ция блочного шифрования
        gcry_md_write (hd, buffer, N);

        loading->setValue(loading->value() + N);

    }

    // Ф-ция блочного шифрования
    gcry_md_write (hd, buffer, N);


    int count = gcry_md_get_algo_dlen(GCRY_MD_STRIBOG512);

    //Ф-ция получение шифрованного текста
    unsigned char *temp = gcry_md_read (hd, 0);

    QString str = "";
    for (int i=0; i < count; ++i)
        str += QString("%1 ").arg(quint8(temp[i]), 0, 16);

    loading->setValue(loading->value() + N);

    return str;

}
