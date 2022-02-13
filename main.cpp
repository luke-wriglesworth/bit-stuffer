#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Bits
{
    private:
        string sequence;
        string packet;

    public:
        Bits()
        {

        }

        string getSequence()
        {
            return sequence ;
        }
        
        string getPacket()
        {
            return packet;
        }
        
        void setSequence(string sequence)
        {
            this->sequence=sequence;
        }
        
        void setPacket(string packet)
        {
            this->packet=packet;
        }

        void toString()
        {
            cout << this->packet << ": " << this->sequence << endl;
        }

};

// The resize function creates a new array one size larger, and copies the old array into it, appending the new Bits object at the end. 
// After it's done it deletes the old dynamic array and updates the size pointer. 
Bits* resize(Bits* obj, Bits* arr, int* size)
{
    int newSize = *size + 1;
    Bits* newArray = new Bits[newSize];
    for (int i = 0; i < *size; i++)
    {
        newArray[i] = arr[i];
    }
    newArray[newSize-1] = *obj;
    delete[] arr;
    *size = newSize;
    return newArray;
}

// getBitsObject() searches a line of text and checks if the given sequence is found within it. 
// If the sequence is found, it returns the packet and sequence as a Bits object.
Bits getBitsObject(string word, string user_sequence)
{
    if(word.find(user_sequence)!=string::npos)
    {        

        Bits newBit;
        //Set Packet
        for (int i = 0; i<word.size(); i++)
        {
            if (word[i]==',')
            {
                newBit.setPacket(word.substr(0,i));
                newBit.setSequence(word.substr(i+1,string::npos));
            }
        }
        return newBit;
    }
    else
    {
        Bits nullBit;
        nullBit.setPacket("");
        nullBit.setSequence("");
        return nullBit;
    }
}

// Outputs each Bits object in the array. 
void display(Bits* arr, int* size)
{
    cout << endl << "************************************ Bit Sequences Found" << "******************************************" << endl << endl;
    for (int i = 0; i < *size; i++)
    {
        arr[i].toString();
    }
    cout << endl << "Total Occurences: " << *size << endl;
    cout << "**************************************************************************************************";
}
int main()
{
    ifstream file;
    string line;
    string user_sequence;

    int initialSize = 0;
    int* sizePtr = &initialSize;
    Bits* bitsArray = new Bits[initialSize];
    
    file.open("bits.txt");
    cout << "Enter a bit sequence: " << endl;
    cin >> user_sequence;

    // The main body of the program first checks if the given sequence is found in a line using getBitsObject()
    // If getsBitsObject() returns a bit that does not have blank values, then the bit will be appended to the dynamic array
    // using resize().
    while(getline(file, line))
    {
        Bits foundBit = getBitsObject(line, user_sequence);
        Bits* foundBitPtr = &foundBit;
        if (foundBit.getSequence()!="")
        {
            bitsArray = resize(foundBitPtr,bitsArray,sizePtr);        
        }
    }

    // Prints all the Bits objects in the final array. 
    display(bitsArray, sizePtr);

    file.close();   
    return 0;
}