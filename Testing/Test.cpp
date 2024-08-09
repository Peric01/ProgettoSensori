using namespace std;
#include <iostream>
#include <random>

typedef unsigned int u_int;

class Sensor
{
protected:
    u_int SensorID;
    std::string Name;
    const std::vector<int> Time = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    float MinValue = 0;
    float MaxValue = 0;
public:
    virtual ~Sensor() = default;
    Sensor(const std::string&);
    u_int getID() const;
    std::string getName() const;
    float getMin() const;
    float getMax() const;
    virtual void Simulation() const =0; /*VOID tipo da sostituire probabilmente*/
};

class PHSensor : public Sensor
{
private:
    std::vector<float> ph_value;
public:
    PHSensor(std::string&);
    ~PHSensor() = default;
    void Simulation() const override;
    void addValue(float value);
};

Sensor::Sensor(const std::string& n) {
        Name = n;
        std::random_device rd;  // Generatore di numeri casuali hardware
        std::mt19937 gen(rd()); // Generatore Mersenne Twister inizializzato con il random device
        std::uniform_int_distribution<> dis(1, 10000); // Distribuzione uniforme tra 1 e 10000

        // Assegnazione di un ID casuale /*DA CONTROLLARE POI SE VIENE SALVATO L'ID, AL MOMENTO OGNI COMPILAZIONE NE CREA UNO NUOVO*/
        SensorID = dis(gen);
}

u_int Sensor::getID() const{
    return SensorID;
}

std::string Sensor::getName() const{
    return Name;
}

float Sensor::getMin() const{
    return MinValue;
}

float Sensor::getMax() const{
    return MaxValue;
}

void PHSensor::Simulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 14);

    std::vector<float> sensorValues;
    for (int i = 0; i < Time.size(); i++) {
        float value = dis(gen);
        sensorValues.push_back(value);
        if (i==0){
            cout << "[";
            cout << value;}
        cout << ", "<< value;
        if (i==Time.size()-1)
            cout << "]" << endl;
    }
}

PHSensor::PHSensor(std::string& n) : Sensor(n){}

void PHSensor::addValue(float value) {
        ph_value.push_back(value);
}

int main(){
    string name = "PHSensor";
    const PHSensor ph(name);
    cout << "ID: " << ph.getID() << endl;
    cout << "Name: " << ph.getName() << endl;
    ph.Simulation();
    return 0;
}