#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int indexHexStrings = 0;
//1 2 1 ,,, 1
const char* hexStrings[] = {
    //:LL AAAA TT DD… CC
    //LL Поле длины — показывает количество байт данных (DD) в записи.
    //AAAA Поле адреса — представляет начальный адрес записи.
    //TT Поле типа.Оно может принимать следующие значения:
    // + 00 запись содержит данные двоичного файла.
    // + 01 запись является концом файла.
    // + 02 запись адреса сегмента(подробнее см.ниже).
    // + 03 Стартовый адрес запуска программы в формате
    // + 80x86(значения регистров CS:IP счетчика команд и регистра смещения)
    // + 04 запись расширенного адреса(подробнее см.ниже).
    // + 05 32 - битный адрес запуска программы в « линейном» адресном пространстве
    ":02_0000_04_0801_F1",
    ":02_0000_02_0400_F8",
    //После этого запись должна идти с  0x0801_4000
    ":10_0010_00_12345678_9ABCDEF0_96385274_14725836_00",
    ":0F_0020_00_A4043111_C0902434_F1125C03_209043_EA",
    ":0F_0030_00_01020B13_05241610_01052401_100900_0D",
    ":04_0000_05_080000C1_2E", //не понял что это?
    ":00_0000_01_FF"
};


// Объявление структуры для хранения данных из строки HEX файла
typedef struct
{
    uint8_t length; // Длина данных в байтах в строке HEX файла
    uint16_t address; // Адрес, к которому относятся данные в строке HEX файла
    uint8_t type; // Тип записи в HEX файле (например, данные, конец файла и т.д.)
    uint8_t* data; // Указатель на данные из строки HEX файла
    uint8_t crc; // Контрольная сумма CRC для данных в строке HEX файла
} HexRecord;

// Функция для вычисления CRC-8
uint8_t calculateCRC(const uint8_t* data, uint8_t length)
{
    uint8_t crc = 0;
    for (int i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x07; // Полином для CRC-8
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// Функция для проверки CRC кода строки HEX файла
int checkCRC(const uint8_t* data, uint8_t length, uint8_t crc)
{
    uint8_t calculatedCRC = calculateCRC(data, length);
    return (calculatedCRC == crc) ? 1 : 0;
}


void writeDataInParts(HexRecord* record, uint32_t address)
{
    uint32_t data32 = 0;
    int dataLength = record->length;
    printf("Итоговый адрес: 0x%X\n", address);
    for (int i = 0; i < dataLength; i++)
    {
        switch (i % 4)
        {
        case 0:
            data32 |= record->data[i] << 24;
            if (i == dataLength - 1)
            {
                data32 |= 0x00FFFFFF;
                printf("data32: 0x%X\n", data32);
            }
            break;
        case 1:
            data32 |= record->data[i] << 16;
            if (i == dataLength - 1)
            {
                data32 |= 0x0000FFFF;
                printf("data32: 0x%X\n", data32);
            }
            break;
        case 2:
            data32 |= record->data[i] << 8;
            if (i == dataLength - 1)
            {
                data32 |= 0x000000FF;
                printf("data32: 0x%X\n", data32);
            }
            break;
        case 3:
            data32 |= record->data[i];
        //HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, address, record->data[i]);
            printf("data32: 0x%X\n", data32);
            address += 4;
            data32 = 0;
            break;
        }
    }
}

void do_work(HexRecord* record)
{
    static uint32_t extendedAddress = 0x0000; // Пример расширенного адреса
    static uint32_t segmentAddress = 0x0000; // Пример адреса сегмента

    switch (record->type)
    {
    case 0x00:
        printf("Data Record: %d bytes\n", record->length);
    // Обработка записи с данными
    // Составления итогового адреса
        uint32_t address = (extendedAddress << 16) + segmentAddress + record->address;;

        writeDataInParts(record, address);
        break;
    case 0x01:
        printf("End of File Record\n");
    // Обработка конца файла
        break;
    case 0x02:
        printf("Segment Address Record\n");
    // Обработка записи адреса сегмента
        segmentAddress = record->data[1]; // Младший байт
        segmentAddress |= (record->data[0]) << 8; // Старший байт
        segmentAddress = segmentAddress << 4; // Старший байт
        break;
    case 0x03:
        printf("Start Address Record\n");
    // Обработка стартового адреса
        break;
    case 0x04:
        printf("Extended Address Record\n");
    // Обработка записи расширенного адреса
        extendedAddress = record->data[1]; // Младший байт
        extendedAddress |= (record->data[0]) << 8; // Старший байт
        break;
    case 0x05:
        printf("32-bit Start Address Record\n");
    // Обработка 32-битного стартового адреса
        break;
    default:
        printf("Unknown Record Type\n");
    // Обработка неизвестного типа записи
        break;
    }
}

// Функция для проверки структуры записи HEX файла и записи данных в внутреннюю флеш память
void processHexRecord(HexRecord* record)
{
    // Реализация проверки записи HEX файла
    //if (checkCRC(&record->data, &record->length, &record->crc))
    {
        do_work(record);
    }
    //else
    {
        //printf("CRC check failed\n");
    }
}

// Функция для чтения строки HEX файла и заполнения структуры HexRecord
void readHexRecord(const char* hexString, HexRecord* record)
{
    // Инициализация структуры с некорректными значениями
    record->length = 0;
    record->address = 0;
    record->type = 0;
    record->data = NULL;
    record->crc = 0;

    // Парсинг строки HEX файла и заполнение структуры HexRecord
    //sscanf(hexString, ":%2hhx%4hx%2hhx", &record.length, &record.address, &record.type);
    // не понял в чём разница маски в плане итогового ответа
    //в каких случаях другое получается?
    sscanf(hexString, ":%2x%4x%2x", &record->length, &record->address, &record->type);

    //Парсинг Данных
    size_t dataLength = (strlen(hexString) - 11) / 2; // Длина данных в строке HEX файла
    record->data = (uint8_t*)malloc(dataLength);
    //record.data = (uint8_t*)malloc(record.length * sizeof(uint8_t));

    for (size_t i = 0; i < dataLength; i++)
    {
        sscanf(hexString + 9 + (i * 2), "%2x", &record->data[i]);
    }

    // Парсинг CRC
    sscanf(hexString + 9 + (dataLength * 2), "%2x", &record->crc);
}

void mainHex()
{
    // Создание массива структур HexRecord
    HexRecord records[indexHexStrings];

    for (int i = 0; i < indexHexStrings; i++)
    {
        readHexRecord(hexStrings[i], &records[i]);

        // Вывод полученной структуры HexRecord
        printf("Record %d:\n", i + 1);
        printf("Length: %d\n", records[i].length);
        printf("Address: 0x%X\n", records[i].address);
        printf("Type: 0x%X\n", records[i].type);
        if (records[i].data != NULL)
        {
            printf("Data: ");
            for (int j = 0; j < records[i].length; j++)
            {
                printf("%02X ", records[i].data[j]);
            }
            printf("\n");
            //free(records[i].data); // Освобождение памяти
        }
        else
        {
            printf("Data: NULL\n");
        }
        printf("CRC: 0x%X\n\n", records[i].crc);
    }


    for (int i = 0; i < indexHexStrings; i++)
    {
        processHexRecord(&records[i]);
    }
}


void refString(void)
{
    for (int i = 0; i < indexHexStrings; i++)
    {
        char* modifiedString = (char*)malloc(strlen(hexStrings[i]) + 1);
        char* currentString = hexStrings[i];
        char* readChar = currentString;
        char* writeChar = modifiedString;

        while (*readChar != '\0')
        {
            if (*readChar != '_')
            {
                *writeChar = *readChar;
                writeChar++;
            }

            readChar++;
        }

        *writeChar = '\0'; // Устанавливаем конец строки
        // Вывод изменённой строки
        //printf("%s\n", modifiedString);
        hexStrings[i] = modifiedString;
        //printf("%s\n", hexStrings[i]);
    }
}


void constructor(void)
{
    indexHexStrings = sizeof(hexStrings) / sizeof(hexStrings[0]);
}

int main()
{
    constructor();
    refString();

    printf("Hello, world!\n");
    mainHex();


    return 0;
}
