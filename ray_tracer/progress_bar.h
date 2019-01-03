#ifndef RAY_TRACER_PROGRESS_BAR_H_
#define RAY_TRACER_PROGRESS_BAR_H_

namespace trace {

class ProgressBar {
 public:
  ProgressBar(int width);
  void Start();
  void Update(double fraction_compled);
  void Finish();

 private:
  const int width_;
  int current_work_units_;
  bool is_first_update_;
};

}  // namespace trace

#endif  // RAY_TRACER_PROGRESS_BAR_H_