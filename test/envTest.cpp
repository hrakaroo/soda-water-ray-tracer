#include <env.h>
#include <color.h>

main()
{
  envf * env = new envf(400, 400);

  colorf color = env->color(200, 210);

  cout << "color: " << color << endl;
}


