#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;




class Capacitor {
public:
   long double capacitance;

    Capacitor(double cap) : capacitance(cap) {}
};

// Class for resistors
class Resistor {
public:
    double resistance;

    Resistor(double res) : resistance(res) {}
};

 long double totalResistorResistance = 0.0;
  long double  totalCapacitorCapacitance = 0.0; //store total capacity every round

int oldlength=0; //store vector lengths in every round
int oldlengthr=0;

 //help function
void help(){
   cout << "Help: Here's how to use the program." << endl;
    cout << "1. Enter capacitors: Allows you to input capacitor values." << endl;
    cout << "2. Enter resistors: Allows you to input resistor values." << endl;
    cout << "5. Clear capacitors and resistors: Clears all entered capacitors and resistors." << endl;
    cout << "6. Charge discharge times: Calculates and displays charge and discharge times." << endl;
    cout << "7. Desired voltage level: Calculates and displays the time to reach a desired voltage level." << endl;
    cout << "8. Desired time: Calculates and displays the voltage after a given time." << endl;
    cout << "h. Help: Displays this help message." << endl;
    cout << "q. Quit: Exits the program." << endl;


}

//round number to two decimal places
double roundToTwoDecimalPlaces(double num) {
    return round(num * 100.0) / 100.0;
}

//print in engineering notation
void engineeringNotation(double value, const std::string& unit) {
    const double kilo = 1.0e3;
    const double mega = 1.0e6;
    const double giga = 1.0e9;

    if (abs(value) >= giga) {
        cout  << roundToTwoDecimalPlaces(value / giga) << " G" << unit ;
    } else if (abs(value) >= mega) {
        cout  << (value / mega) << " M" << unit ;
    } else if (abs(value) >= kilo) {
        cout  << roundToTwoDecimalPlaces(value / kilo) << " k" << unit ;
    } else if (abs(value) >= 1.0) {
        cout  << roundToTwoDecimalPlaces(value) << " " << unit ;
    } else if (abs(value) >= 1.0e-3) {
        cout  << roundToTwoDecimalPlaces(value * kilo) << " m" << unit ;
    } else if (abs(value) >= 1.0e-6) {
        cout  << roundToTwoDecimalPlaces(value * mega) << " micro" << unit;
    } else if (abs(value) >= 1.0e-9) {
        cout << roundToTwoDecimalPlaces(value * giga) << " n" << unit ;
    } else {
        cout << "Value too small for engineering notation." << endl;
    }
}


//calculate precentages
void calculateTimes(double resistance, double capacitance,double finalVoltage) {
    double RC = resistance * capacitance;
    vector<double> chargeLevels = {0.01, 0.15, 0.35, 0.50, 0.65, 0.85, 0.99};
    cout << "RC constant for this configuration: " << RC << endl;
    cout << "Charge and discharge times:" << endl;
    cout << left << "\t" << "Level" << "\t" << "Charge Time" << "\t" << "Discharge Time" << endl;

    for (double level : chargeLevels) {
             double chargeTime = (-1*RC) * log(((finalVoltage*level) - finalVoltage) / (0-finalVoltage));

        double dischargeTime = -RC * log(level);

        cout << (level * 100)<< "%"<<"\t";

        engineeringNotation(chargeTime,"s");

cout<<"\t";
          engineeringNotation( dischargeTime,"s");
cout<< endl;
    }
    cout << endl;

    // Append results to CSV file
    ofstream outFile("Capacitor Configurations.csv", ios::app);
    if (outFile.is_open()) {
        outFile << resistance << "," << capacitance << "," << RC << ",";
        for (double level : chargeLevels) {
         double chargeTime = (-1*RC) * log(((finalVoltage*level) - finalVoltage) / (0-finalVoltage));

            double dischargeTime = -RC * log(level);
            outFile << chargeTime << "," << dischargeTime << ",";
        }
        outFile << endl;
        outFile.close();
        cout << "Results appended to 'Capacitor Configurations.csv'" << endl;
    } else {
        cout << "Unable to open 'Capacitor Configurations.csv' for writing." << endl;
    }
}



//calculate Total Resistance
double calculateTotalResistance(const vector<Resistor>& resistors, char connectionType) {

     double newtotalResistorResistance = 0.0;

    if (connectionType == 's' || connectionType == 'S') {

         for (int i=oldlengthr;i < resistors.size(); ++i) {
           newtotalResistorResistance += resistors[i].resistance;
        }
    } else if (connectionType == 'p' || connectionType == 'P') {
        for (int i=oldlengthr;i < resistors.size(); ++i) {
            newtotalResistorResistance += (1.0 / resistors[i].resistance);
        }
        newtotalResistorResistance = 1.0 / newtotalResistorResistance;
    } else {
        cout << "Invalid resistor connection type." << endl;
    }
totalResistorResistance +=newtotalResistorResistance;
oldlengthr=resistors.size();
    return totalResistorResistance;
}

//-----calculate Total Capacitance---------

long double calculateTotalCapacitance(const vector<Capacitor>& capacitors, char connectionType) {

long double newtotalCapacitorCapacitance=0.0;
    if (connectionType == 's' || connectionType == 'S') {
        for (int i=oldlength;i < capacitors.size(); ++i) {

            newtotalCapacitorCapacitance += (1.0 / capacitors[i].capacitance);
        }
        newtotalCapacitorCapacitance = (1.0 / newtotalCapacitorCapacitance);
    } else if (connectionType == 'p' || connectionType == 'P') {
        for (int i=oldlength;i < capacitors.size(); ++i) {

            newtotalCapacitorCapacitance += capacitors[i].capacitance;

        }
    } else {
        cout << "Invalid capacitor connection type." << endl;
    }

if(totalCapacitorCapacitance==0.0){
       totalCapacitorCapacitance=newtotalCapacitorCapacitance;
}
else{
    totalCapacitorCapacitance=1.0/totalCapacitorCapacitance;
    totalCapacitorCapacitance+=(1.0/newtotalCapacitorCapacitance);
    totalCapacitorCapacitance=1/totalCapacitorCapacitance;
}


oldlength=capacitors.size();
    return totalCapacitorCapacitance;
}


int main() {

    //display a Welcome message
     cout << "Turing Moore Engineering Capacitor Simulator 1.0" << endl;
    cout << "Your name: [Your Name]" << endl; // Replace [Your Name] with your actual name
    cout << "Your Student ID: [Your Student ID]" << endl; // Replace [Your Student ID] with your actual student ID

    // Get the current date and format it


    cout << "Date the assignment is due: "<<"[date]"<<endl;

    cout << "Desired Level: HD" << endl;
    // Get circuit voltage
    double circuitVoltage;
    cout << "Enter circuit voltage (in Volts): ";
    cin >> circuitVoltage;

    vector<Capacitor> capacitors;
    vector<Resistor> resistors;

    char choice;
    bool quit = false;
  char resistorConnection;
    char capacitorConnection;

    while (!quit) {
        cout << "\nMenu:" << endl;
        cout << "1. Enter capacitors" << endl;
        cout << "2. Enter resistors" << endl;

        cout << "3. Clear capacitors and resistors" << endl;
        cout << "4. Charge discharge times" << endl;
        cout << "5. Desired voltage level" << endl;
        cout << "6. Desired time" << endl;
         cout << "7. change circuit voltage" << endl;
        cout << "h. Help" << endl;
        cout << "q. Quit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') { // Enter capacitors
            int numCapacitors;
            cout << "Enter the number of capacitors: ";
            cin >> numCapacitors;

            for (int i = 0; i < numCapacitors; ++i) {
                long double capValue;
                cout << "Enter capacitance value for capacitor " << i + 1 << " (in Farads): ";
                cin >> capValue;
                capacitors.push_back(Capacitor(capValue));
            }

            cout << "Are the capacitors in series (s) or parallel (p)? ";
            cin >> capacitorConnection;
           calculateTotalCapacitance(capacitors, capacitorConnection);


                              cout << "toatal capacitance";
                              engineeringNotation(totalCapacitorCapacitance,"F");
                              cout<< endl;



        } else if (choice == '2') { // Enter resistors
            int numResistors;
            cout << "Enter the number of resistors: ";
            cin >> numResistors;

            for (int i = 0; i < numResistors; ++i) {
                double resValue;
                cout << "Enter resistance value for resistor " << i + 1 << " (in Ohms): ";
                cin >> resValue;
                resistors.push_back(Resistor(resValue));
            }


            cout << "Are the resistors in series (s) or parallel (p)? ";
            cin >> resistorConnection;
             double totalResistorResistance = calculateTotalResistance(resistors, resistorConnection);
            cout<<"total Resistor Resistance ";
             engineeringNotation(totalResistorResistance,"Ohm");
             cout<< endl;

        }  else if (choice == '3') { // Clear capacitors and resistors
            capacitors.clear();
            resistors.clear();
            totalResistorResistance = 0.0;
            totalCapacitorCapacitance = 0.0; //clear total capacity every round

            oldlength=0; //clear vector lengths in every round
            oldlengthr=0;
            cout << "Capacitors and resistors cleared." << endl;
        } else if (choice == '4') { // Charge discharge times
            if (resistors.empty() || capacitors.empty()) {
                cout << "Please enter at least one resistor and one capacitor before calculating times." << endl;
            } else {


                    calculateTimes(totalResistorResistance,totalCapacitorCapacitance,circuitVoltage);

            }
        } else if (choice == '5') {
            if (resistors.empty() || capacitors.empty()) {
        cout << "Please enter at least one resistor and one capacitor before calculating times." << endl;
    } else {

            double initialVoltage;
            double finalVoltage=circuitVoltage;
            cout << "Enter  voltage (Vi in Volts): ";
            cin >> initialVoltage;


            double RC =totalResistorResistance  * totalCapacitorCapacitance;

            if (initialVoltage > finalVoltage) {
                cout << "The desired voltage level must be higher than the initial voltage." << endl;
            } else {

                double time = (-1*RC) * log((initialVoltage - finalVoltage) / (0-finalVoltage));

if(time<0){
    time*=-1;
}
                cout << "Time to reach the desired voltage level: ";
                 engineeringNotation(time,"s");
                 cout<< endl;

            }
        }

        } else if (choice == '6') {
           if (resistors.empty() || capacitors.empty()) {
        cout << "Please enter at least one resistor and one capacitor before calculating times." << endl;
    } else {


            double initialVoltage=0;
            double time;

            cout << "Enter time (t in seconds): ";
            cin >> time;

               double RC =totalResistorResistance  * totalCapacitorCapacitance;
            double finalVoltage = circuitVoltage; // Set final voltage as the circuit voltage

            if (time >= 0) {
                double voltage = finalVoltage + (0- finalVoltage) * exp(-1*(time / RC));
                cout << "Voltage after " << time << " seconds: " << voltage << " Volts" << endl;
            } else {
                cout << "Time must be a non-negative value." << endl;
            }
        }

        }
        else if(choice=='7'){
                cout << "Enter circuit voltage (in Volts): ";
    cin >> circuitVoltage;
        }
         else if (choice == 'h') { // Help
           help();
        } else if (choice == 'q') { // Quit
            cout << "Exiting program." << endl;
            quit = true;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
