#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// This structure represents a Singly Linked List data structure.
struct ЭлементОдносвязногоСписка {
    int значение;
    ЭлементОдносвязногоСписка* следующий;

    ЭлементОдносвязногоСписка(int з) {
        this->значение = з;
    }
};

// This structure represents a Queue data structure.
struct Очередь
{
public:
    Очередь(int вместимость)
    {
        _мас = new int[вместимость];

        _колво = 0;

        _вместимость = вместимость;
    }

    ~Очередь()
    {
        delete[] _мас;
    }

    bool Засунуть(int знач)
    {
        if (Полна()) return false;

        вставитьБезПроверки(знач);
        return true;
    }

    int Вынуть()
    {
        if (Пуста())
        {
            throw new std::runtime_error("queue is empty");
        }

        auto frontElement = получитьПередний();

        подвинутьВнутреннийМассивВверх();

        return frontElement;
    }

    bool Пуста()
    {
        return !_колво;
    }

    bool Полна()
    {
        return _колво == _вместимость;
    }

    int ПолучитьКоличество()
    {
        return _колво;
    }

    void Отобразить()
    {
        for (auto и = 0; и < _колво; и++)
        {
            cout << _мас[и] << endl;
        }
    }

private:
    int* _мас;
    int _вместимость;
    int _колво;

    void вставитьБезПроверки(int знач)
    {
        _мас[_колво] = знач;
        _колво++;
    }

    void подвинутьВнутреннийМассивВверх()
    {
        for (int i = 0; i < _колво - 1; i++)
        {
            _мас[i] = _мас[i + 1];
        }

        _колво--;
    }

    int получитьПередний()
    {
        return _мас[0];
    }
};

// This is an entry point for an application.
int main() {
    ЭлементОдносвязногоСписка* голова;
    ЭлементОдносвязногоСписка* зад;
    int колво = 0;

    ifstream чтец("./input.txt");
    string строчка;
    while (чтец >> строчка) {
        колво++;

        auto узел = new ЭлементОдносвязногоСписка(
            stoi(строчка)
        );

        if (!голова) {
            голова = узел;
            зад = узел;
            continue;
        }

        зад->следующий = узел;
        зад = узел;
    }
    чтец.close();

    cout << "Read into LinkedList successfully." << endl;

    Очередь очередь(колво);

    auto текущийУзел = голова;
    while (1)
    {
        очередь.Засунуть(текущийУзел->значение);

        if (очередь.Полна()) break;

        текущийУзел = текущийУзел->следующий;
    }

    очередь.Отобразить();
    cout << "Copied into Queue successfully." << endl;

    ofstream писарь("./output.txt");
    while (!очередь.Пуста())
    {
        auto число = очередь.Вынуть();
        cout << число << " ";
        писарь << число << " ";
    }
    писарь.close();
}
