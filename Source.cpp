#include <ipp.h>
#include <string>
#include <vector>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <deque>


class member
{
public:
  member(unsigned int joined_month)
    :_joined_month(joined_month)
  {
  }

  unsigned int joined_month(){return _joined_month;}

private:
  unsigned int _joined_month;


};

class society
{
public:
  society()
  {
    _population = 70000000;
    _termination_time = 6;
    _profit_time = 2; //6 child: it happened in second month
  }

  society(unsigned long long int population, unsigned int termination_time, unsigned int profit_time)
  :_population(population),
   _termination_time(termination_time),
   _profit_time(profit_time)
  {

  }
  int draw(unsigned long long int profite_member, unsigned long long int current_member, unsigned int current_month)
  {
    cv::Mat out(540, 960, CV_8UC3);


    unsigned long long int non_profite_member = current_member - profite_member;



    //Member
    {
      cv::line(out,cv::Point(40,275) , cv::Point(700,275), cv::Scalar(255,255,255));
      cv::putText(out, "Month", cv::Point(705,275), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.4, cvScalar(255,255,250), 1, CV_AA);
      cv::line(out,cv::Point(40,275) , cv::Point(40,10), cv::Scalar(255,255,255));
      cv::putText(out, "Population", cv::Point(50,10), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.4, cvScalar(255,255,250), 1, CV_AA);

      unsigned int pixels_member = current_member * 255 / _population;
      if(member_per_mount.size() == 0) member_per_mount.push_back(std::pair<unsigned long long int, int>(pixels_member+1, current_month));
      else if(member_per_mount.back().second == current_month)  member_per_mount.back().first =(pixels_member+1);
      else member_per_mount.push_back(std::pair<unsigned long long int, int>(pixels_member+1, current_month));

      int lenght = 30;
      for(size_t i = 0 ; i < member_per_mount.size();i++)
        for(size_t j = 270; j > 270-member_per_mount[i].first ; j--)
          for(size_t k = 50 ; k < 50+lenght ; k++)
          {
            int color = 255 - member_per_mount[i].first;
            if(color > 255) color =255;
            if(color < 50 ) color = 50;
            out.data[out.step[0]*j + (out.step[1]* (k+(i*lenght))) + 0] = color;
          }

    }

    //Profit
    {

      cv::line(out,cv::Point(40,501) , cv::Point(350,501), cv::Scalar(255,255,255));
      cv::putText(out, "With profit", cv::Point(75,520), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.4, cvScalar(255,255,250), 1, CV_AA);
      cv::putText(out, "Without profit", cv::Point(225,520), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.4, cvScalar(255,255,250), 1, CV_AA);
      cv::line(out,cv::Point(40,501) , cv::Point(40,300), cv::Scalar(255,255,255));
      cv::putText(out, "Number", cv::Point(50,300), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.4, cvScalar(255,255,250), 1, CV_AA);

      unsigned int pixels_profite = (profite_member * 200 / _population)+1;
      unsigned int pixels_non_profite = (non_profite_member * 200 / _population)+1;

      int lenght = 100;
      for(size_t i = 500; i > 500-pixels_profite ; i--)
        for(size_t j = 50 ; j < 50+lenght ; j++)
          out.data[out.step[0]*i + out.step[1]* j + 1] = 255;
      for(size_t i = 500; i > 500-pixels_non_profite ; i--)
        for(size_t j = 200 ; j < 200+lenght ; j++)
          out.data[out.step[0]*i + out.step[1]* j + 2] = 255;
    }


    {
      std::string Result; 
      std::ostringstream convert;
      convert << current_month;      // insert the textual representation of 'Number' in the characters in the stream
      Result = "Current month: " + convert.str(); 
      cv::putText(out, Result, cv::Point(500,440), 
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    }
    {
      std::string Result; 
      std::ostringstream convert;
      convert << current_member;      // insert the textual representation of 'Number' in the characters in the stream
      Result = "Current members: " + convert.str(); 
      cv::putText(out, Result, cv::Point(500,460), 
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    }      {
      std::string Result; 
      std::ostringstream convert;
      convert << profite_member;      // insert the textual representation of 'Number' in the characters in the stream
      Result = "Member with profit: " + convert.str(); 
      cv::putText(out, Result, cv::Point(500,480), 
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    }
    {
      std::string Result; 
      std::ostringstream convert;
      convert << non_profite_member;      // insert the textual representation of 'Number' in the characters in the stream
      Result = "Member without profit: " + convert.str(); 
      cv::putText(out, Result, cv::Point(500,500), 
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    }

    cv::imshow("Result", out);
    cv::waitKey(3);
    return 1;
  }

  unsigned long long int population(){return _population;}
  unsigned int termination_time(){return _termination_time;}
  unsigned int profit_time(){return _profit_time;}

private:
  unsigned long long int _population;
  unsigned int _termination_time;
  unsigned int _profit_time;
  std::vector<std::pair<unsigned long long int,int>> member_per_mount;
};

int main()
{

  int in_para = -1;
  while(in_para != 89 && in_para != 121 && in_para!= 78 && in_para != 110)
  {
    std::cout << std::endl<<"Use default parameters? (y/n)"<<std::endl;
    std::cout << "Default parameters are:"<<std::endl<<"  Population: 70,000,000" <<std::endl<<
      "  Give up period: 6 months"<<std::endl<<
      "  Receive profit after having 6 members"<<std::endl;
    in_para = getchar(); 
  }

  society country;
  if(in_para == 78 || in_para == 110) //No
  {
    unsigned long long int pop;
    unsigned int termperiod;
    int prof_mem;
    std::cout << std::endl;
    std::cout << "Enter population(e.g. 70000000): ";
    std::cin>> pop;

    std::cout << std::endl;
    std::cout << "Enter give up period(e.g. 6): ";
    std::cin>> termperiod;


    std::cout << std::endl;
    std::cout << "Enter number of member to gain profit(e.g. 6): ";
    std::cin>> prof_mem;
    unsigned int prof_period = 0;
    while(prof_mem > 0)
    {
      prof_period++;
      prof_mem -= pow(2, prof_period);

    }


    country = society(pop, termperiod, prof_period);

  }
 

  unsigned long long int profite_member = 0;
  unsigned long long int current_member = 1;
  unsigned int current_month = 1;
  std::deque<member> members;

  members.push_back(member(current_month-1));


  while(1)
  {

    for(size_t i = 0 ; i < members.size() ; i++)
    {
      if (( current_month - members.front().joined_month()) == (country.termination_time()+1) )
        members.pop_front();
      else
        break;
    }
    unsigned int membersize = members.size();
    for(size_t i = 0 ; i < membersize; i++)
    {
      members.push_back(member(current_month));
      current_member++;
      if(current_member >= (country.population())) break;
      members.push_back(member(current_month));
       current_member++;
      if(current_member >= (country.population())) break;
      if(i%10000 == 0)  country.draw(profite_member,current_member,current_month);
    }

    for(size_t i = 0 ; i < members.size(); i++)
    {
      if(current_member >= (country.population()-1)) break;
      if (( current_month - members[i].joined_month()) == country.profit_time())
        profite_member++;
      else if((current_month - members[i].joined_month()) < country.profit_time())
        break;
      if(i%10000 == 0)  country.draw(profite_member,current_member,current_month);
    }




    country.draw(profite_member,current_member,current_month);
    if(current_member >= (country.population())) break;
    current_month++;

  }



   country.draw(profite_member,current_member,current_month);
   std::cout << "Press any key..."<<std::endl;
   cv::waitKey();
   getchar();
  return 1;
}
