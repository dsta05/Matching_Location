#include <iostream>
#include <list>
#include <sstream>

/*
 
 Matching Locations
    Write a program that reads names of places and their geographical coordinates in the format name,latitude,longitude (where latitude and longitude are floating-point numbers). No two locations will have the same name. Some locations may have the same coordinates. After all locations are entered, a single line containing the '.' (dot) the character will be entered. After that, queries will be entered – the queries will either contain a name of a location, or latitude and longitude coordinates (entered as two floating point numbers separated by a single space). Print all locations that match the query in the same format that they were entered. After all queries are entered, a single line containing the '.' (dot) the character will be entered.
 
 */

using namespace std;

class GeoLocation{
  
    private:
    
        string latitude;
        string longitude;
        
    public:
    
        GeoLocation() {}
    
        GeoLocation(string lat, string lng) : latitude(lat), longitude(lng) {}
    
        GeoLocation(istream & istr){
            readGeoLocation(istr);
        }
        
        string getLat(void) const { return latitude; }
    
        string getLng(void) const { return longitude; }
    
        void readGeoLocation(istream & istr){
            
            getline(istr, latitude, ',');
            getline(istr, longitude, ',');
            
        }
    
        const void printDataGL(ostream & ostr){
            
            ostr << latitude << "," << longitude;
            
        }
    
};

class Location{
    
    private:
    
        string name;
        GeoLocation geoLoc;
    
    public:
        
        Location(){}
        
        Location(string name_, string lat_, string lng_) : name(name_), geoLoc(lat_, lng_) {}
    
        Location(istream & istr) {
            readLocaction(istr);
            geoLoc.readGeoLocation(istr);
        }
    
        const string getName(void) const {return name; }
    
        void readLocaction(istream & istr){
            
            getline(istr, name, ',');
            geoLoc.readGeoLocation(istr);
            
        }
    
        const void printData(ostream & ostr){
            
            ostr << name << ",";
            geoLoc.printDataGL(ostr);
            ostr << endl;
        }
    
        const GeoLocation & getGeoLoc(void) { return geoLoc; }
    
};

int main(int argc, const char * argv[]) {

    typedef list<Location> LocList;
    
    LocList data;
    
    // read and record the input information
    while (true) {
        
        string input;
        getline(cin, input);
        
        if(input == "."){
            break;
        }
        
        istringstream istr(input);
        
//        Location tmp;
//        tmp.readLocaction(istr);
//        loc.push_back(tmp);
            
        data.push_back(Location(istr));
        
    }
    
    // read queries
    
    while (true) {
        
        string query;
        getline(cin, query);
        
        if (query == ".") {
            break;
        }
        
        bool isCity = *query.begin() > '9';
        
        GeoLocation curLoc;
        
        if (!isCity) {
            
            istringstream istr(query);
            curLoc.readGeoLocation(istr);
            
        }
        
        LocList :: iterator it = data.begin();
        
        while (it != data.end()) {
            if (isCity) {
                if (it -> getName() == query) {
                    
                    it -> printData(cout);
                    
                }
            } else {
                
                if (it -> getGeoLoc().getLat() == curLoc.getLat() && it -> getGeoLoc().getLng() == curLoc.getLng()) {
                    it -> printData(cout);
                }
                
            }
            
            it++;
            
        }
        
    }
    
    
    return 0;
}


/*
 
 input:
 
Sofia,42.70,23.33
New York,40.6976701,-74.2598732
SoftUni,42.70,23.33
.
 
 */
