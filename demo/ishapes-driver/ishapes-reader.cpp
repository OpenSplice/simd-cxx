// Std C++ Include
#include <algorithm>

// Utils 
#include "util.hpp"

int main(int argc, char* argv[]) {
  try {
    DomainParticipant dp(0);
    Topic<ShapeType> topic(dp, "Circle");
    Subscriber sub(dp);
    DataReader<ShapeType> dr(sub, topic);
      
    uint32_t sleepTime = 100000;

    while (true) {
      // If you can use C++11 then the "auto" keywork and "lambda"
      // function can make this code even nicer.

      LoanedSamples<ShapeType> samples = 
	dr.selector()
	.filter_state(DataState::any_data())
	.read();
      std::cout << "--------------------------------------------" << std::endl;      
      std::for_each(samples.data().begin(), samples.data().end(), printShape);
      usleep(sleepTime);
    }
  } catch (const dds::core::Exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}