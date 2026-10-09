struct Data {
  double ax;
  double ay;
  double az;
  double gx;
  double gy;
  double gz;
  double time;

  Data(double ax, double ay, double az, double gx, double gy, double gz, double time) : 
       ax(ax), ay(ay), az(az), gx(gx), gy(gy), gz(gz), time(time) {}
  
  Data() : Data(0,0,0,0,0,0,0) {}

  String toString(){
    return String(ax) + ", " + String(ay) + ", " + String(az) + ", " + String(gx) + ", " + String(gy) + ", " + String(gz) + ", " + String(time); 
  }
};


