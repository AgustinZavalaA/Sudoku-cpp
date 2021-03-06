class Coordinate {
   private:
    int  data;
    int  visibility;
    bool valid;

   public:
    Coordinate();
    ~Coordinate();
    int  getData();
    void setData(int);
    bool getValid();
    void setValid(bool);
    int  getVisibility();
    void setVisibility(int);
};

Coordinate::Coordinate() {
    data       = 0;
    visibility = 0;
    valid      = true;
}

Coordinate::~Coordinate() {}

int Coordinate::getData() { return data; }

void Coordinate::setData(int d) { data = d; }

bool Coordinate::getValid() { return valid; }

void Coordinate::setValid(bool v) { valid = v; }

int Coordinate::getVisibility() { return visibility; }

void Coordinate::setVisibility(int v) { visibility = v; }