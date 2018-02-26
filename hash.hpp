#ifndef HASH_HPP
#define HASH_HPP

#include <qglobal.h>
#include <QProgressBar>
#include <gcrypt.h>

class Hash
{
public:
    Hash();

    bool Open();

    void Close();

    QString hashing(QString File_name, QProgressBar *loading);
private:

    gcry_md_hd_t hd;
};

#endif // HASH_HPP
