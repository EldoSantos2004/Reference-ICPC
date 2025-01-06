struct Point{
  ll x,y;
  
  Point () : x(), y() {}
  Point (ll _x, ll _y) : x(_x), y(_y){}
  
  Point operator + (const Point &a) const {
    return Point(x+a.x,y+a.y);
  }
  
  Point operator - (const Point &a) const {
    return Point(x-a.x, y-a.y);
  }
  
  // dot product
  // positivo si el angulo entre los vectores es agudo
  // 0 si son perpendiculares
  // negativo si el angulo es obtuso
  ll operator % (const Point &a) const {
    return x*a.x+y*a.y;
  }
  
  // cross product
  // positivo si el segundo esta en sentido antihorario
  // 0 si el angulo es 180
  // negativo si el segundo esta en sentido horario
  ll operator * (const Point &a) const {
    return x*a.y - y * a.x;
  }
};