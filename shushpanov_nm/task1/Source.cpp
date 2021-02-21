#include <iostream>
using namespace std;

class ScaleConverter
{
private:
    bool check = true;
    double weight, originalWeight;
public:
    void scanWeight()
    {
        while (check)
        {
            cout << "������� ��� � ����������� (���� ����� �� �����, ������� ���: 3.5): ";
            cin >> originalWeight;
            if (originalWeight < 0)
            {
                cout << "�������� ������������� ��������, ��������� �������� ������ � �������������� �������. ����������, ���������� ��� ���. \n" << endl;
            }
            else
            {
                check = false;
            }
        }
    }
    void printOriginalWeight()
    {
        cout << "�������� ��� = " << originalWeight << "��" << "\n" << endl;
    }
    void printConvertWeight(char* str)
    {
        cout << "������� " << originalWeight << "�� = " << weight << str << "\n" << endl;
    }
    void convertGrams()
    {
        weight = originalWeight * 1000;
    }
    void convertPharmacyPound()
    {
        weight = originalWeight * 2.679;
    }
    void convertTroyOunce()
    {
        weight = originalWeight * 32.151;
    }
    void convertPood()
    {
        weight = originalWeight / 16.381;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int indexMenu = 0;
    bool end = true;
    char* str;
    ScaleConverter convert;
    convert.scanWeight();
    cout << "\n��������� �����: \n" << "1. ��������� ���������� � ������;\n" << "2. ��������� ���������� � �������� ����;\n"
        << "3. ��������� ���������� � �������� �����;\n" << "4. ��������� ���������� � ����;\n" << "5. ������� ���������� �������� ����������;\n"
        << "6. ����� �� ���������. \n" << endl;
    while (end)
    {
        cout << "�������� ����� ����: ";
        cin >> indexMenu;
        cout << endl;
        switch (indexMenu)
        {
            case 1:
            {
                convert.convertGrams();
                str = " �����";
                convert.printConvertWeight(str);
                break;
            }
            case 2:
            {
                convert.convertPharmacyPound();
                str = " �������� ������";
                convert.printConvertWeight(str);
                break;
            }
            case 3:
            {
                convert.convertTroyOunce();
                str = " �������� �����";
                convert.printConvertWeight(str);
                break;
            }
            case 4:
            {
                convert.convertPood();
                str = " ���";
                convert.printConvertWeight(str);
                break;
            }
            case 5:
            {
                convert.printOriginalWeight();
                break;
            }
            case 6:
            {
                cout << "�� ��������! ������� ��� ��������������� ����� ����������!\n" << endl;
                end = false;
                break;
            }
            default:
            {
                cout << "������ ����� ���� �� ������, ���������� ��� ���!" << endl << endl;
                break;
            }
        }
    }
    system("pause");
    return 0;
}