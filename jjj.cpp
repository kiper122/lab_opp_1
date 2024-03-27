#include <iostream>
#include <cmath>
using namespace std;

struct myVector
{
    int lengthArrayVector;
    double *noZirroElements;
    int lengthNoZirroElements;
    double *indexNoZirroElements;
    int lengthIndexNoZirroElements;
    double *vector;
};

class SparseVector
{
private:
    myVector someVector;

public:
    SparseVector(double *vector, int length)
    {
        someVector.vector = vector;
        someVector.lengthArrayVector = length;
        someVector.noZirroElements = new double[length];
        someVector.indexNoZirroElements = new double[length];
        someVector.lengthNoZirroElements = 0;
        someVector.lengthIndexNoZirroElements = 0;
        addNoZirroElements(someVector);
    }

private:
    void addElement(double *&array, int &size, double newValue)
    {
        double *newArray = new double[size + 1];
        for (int i = 0; i < size; ++i)
        {
            newArray[i] = array[i];
        }
        newArray[size] = newValue;
        delete[] array;
        array = newArray;
        size++;
    }

    void removeElement(double *&array, int &size, int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "error" << endl;
            return;
        }
        double *newArray = new double[size - 1];
        for (int i = 0; i < index; ++i)
        {
            newArray[i] = array[i];
        }
        for (int i = index; i < size - 1; ++i)
        {
            newArray[i] = array[i + 1];
        }
        delete[] array;
        array = newArray;
        size--;
    }

    void addNoZirroElements(myVector &smVector)
    {
        for (int i = 0; i < smVector.lengthArrayVector; i++)
        {
            if (smVector.vector[i] != 0)
            {
                double k = i;
                addElement(smVector.noZirroElements, smVector.lengthNoZirroElements, smVector.vector[i]);
                addElement(smVector.indexNoZirroElements, smVector.lengthIndexNoZirroElements, k);
            }
        }
    }
    void sortNoZirroArrayForIndex()
    {
        for (int i = 0; i < someVector.lengthIndexNoZirroElements; ++i)
        {
            for (int j = 0; j < someVector.lengthIndexNoZirroElements - i - 1; ++j)
            {
                if (someVector.indexNoZirroElements[j] > someVector.indexNoZirroElements[j + 1])
                {
                    int temp = someVector.indexNoZirroElements[j];
                    someVector.indexNoZirroElements[j] = someVector.indexNoZirroElements[j + 1];
                    someVector.indexNoZirroElements[j + 1] = temp;

                    int temp2 = someVector.noZirroElements[j];
                    someVector.noZirroElements[j] = someVector.noZirroElements[j + 1];
                    someVector.noZirroElements[j + 1] = temp2;
                }
            }
        }
    }

public:
    void vectorInfo()
    {
        cout << "No Zirro Elements :" << endl;
        cout << endl;
        for (int i = 0; i < someVector.lengthNoZirroElements; i++)
        {
            cout << "index :" << someVector.indexNoZirroElements[i] << " value :";
            cout << someVector.noZirroElements[i] << endl;
        }
    }
    void plus(double *newVector, int length)
    {
        int indexNoZirro = 0;
        bool isAdd = false;
        if (length <= someVector.lengthArrayVector)
        {
            for (int i = 0; i < someVector.lengthArrayVector; i++)
            {

                for (int k = 0; k < someVector.lengthIndexNoZirroElements; k++)
                {
                    if (someVector.indexNoZirroElements[k] == i)
                    {
                        someVector.noZirroElements[indexNoZirro] += newVector[i];
                        ++indexNoZirro;
                        isAdd = true;
                        break;
                    }
                    else
                    {
                        isAdd = false;
                    }
                }
                if (!isAdd)
                {
                    addElement(someVector.noZirroElements, someVector.lengthNoZirroElements, newVector[i]);
                    addElement(someVector.indexNoZirroElements, someVector.lengthIndexNoZirroElements, i);
                }
            }
            sortNoZirroArrayForIndex();
        }
    }
    void minus(double *newVector, int length)
    {
        int indexNoZirro = 0;
        bool isAdd = false;
        if (length <= someVector.lengthArrayVector)
        {
            for (int i = 0; i < someVector.lengthArrayVector; i++)
            {
                for (int k = 0; k < someVector.lengthIndexNoZirroElements; k++)
                {
                    if (someVector.indexNoZirroElements[k] == i)
                    {
                        someVector.noZirroElements[indexNoZirro] -= newVector[i];
                        if (someVector.noZirroElements[indexNoZirro] == 0)
                        {
                            removeElement(someVector.noZirroElements, someVector.lengthNoZirroElements, indexNoZirro);
                            removeElement(someVector.indexNoZirroElements, someVector.lengthIndexNoZirroElements, indexNoZirro);
                        }
                        ++indexNoZirro;
                        isAdd = true;
                        break;
                    }
                    else
                    {
                        isAdd = false;
                    }
                }
                if (!isAdd)
                {
                    double value = 0 - newVector[i];
                    addElement(someVector.noZirroElements, someVector.lengthNoZirroElements, value);
                    addElement(someVector.indexNoZirroElements, someVector.lengthIndexNoZirroElements, i);
                }
            }
        }
        sortNoZirroArrayForIndex();
    }
    void multiplication_a_number(double number)
    {
            for (int i = 0; i < someVector.lengthIndexNoZirroElements; i++)
            {
                someVector.noZirroElements[i] *= number;
            }
    }
    void modulVector()
    {
        int result = 0;
        for (int i = 0; i < someVector.lengthNoZirroElements; i++)
        {
            result += pow(someVector.noZirroElements[i], 2);
        }
        cout << "Modul Vector is  :"
             << "  " << sqrt(result);
    }
    void scalarProduct(double *newVector, int length)
    {
        int result = 0;
        int indexNoZirroElement = 0;
        if (length <= someVector.lengthArrayVector)
        {
            for (int i = 0; i < someVector.lengthNoZirroElements; i++)
            {
                for (int k = 0; k < someVector.lengthIndexNoZirroElements; k++)
                {
                    if (newVector[i] != 0 && someVector.indexNoZirroElements[k] == i)
                    {
                        result += newVector[i] * someVector.noZirroElements[indexNoZirroElement];
                        ++indexNoZirroElement;
                    }
                }
            }
        }
        cout << "scalarProduct Vectors 1 and 2 is :  " << result << endl;
    }
};

int main()
{
    double b[] = {1.5,0,0,3,0,2};
    double h[] = {4,45,0,9,};
    SparseVector f(b, 6);
    f.vectorInfo();
    f.scalarProduct(h,4);
    return 0;
}
