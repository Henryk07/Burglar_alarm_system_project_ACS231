// header file m_fr.h
// this is the specification of the class m_fr
class m_fr{
  private:
  const int max_attempts=3;
  double lastlock_time=0;
  int lockstatus=0;
  int sys_attempts=0;
  public:
  int check_works();
  int check_lockstatus();
  int check_attempts();
  int set_attempts();
  int check_locktime();
};
