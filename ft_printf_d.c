#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

void  ft_putchar(char c)
{
  write(1, &c, 1);
}

void  ft_putstr(char *s)
{
  while (*s)
  {
    ft_putchar(*s);
    s++;
  }
}

int  ft_nbrlen(int nbr)
{
  int len = 0;
  if (nbr == INT_MIN)
    return (11);
  if (nbr < 0)
  {
    nbr *= -1;
    len++;
  } 
  while (nbr > 0)
  {
    nbr /= 10;
    len++;
  }
  return (len);
}

char  *ft_itoa(int nbr)
{
  char  *p;
  int len = ft_nbrlen(nbr);
  p = (char *)malloc(sizeof(char) * (len + 1));
  if (!p)
    return (NULL);
  p[len] = '\0';
  while (nbr > 0)
  {
    p[--len] = nbr % 10 + '0';
    nbr /= 10;
  }
  return (p); 
}

void  ft_printf_d(char *s, ...)
{
  int wid = 0;
  int prec= 0;
  int len_arg;
  int nbr;
  char *p;
  va_list ap;
  va_start(ap, s);
  while(*s)
  {
    if (*s != '%')
    {
      ft_putchar(*s);
      s++;
    }
    else
    {
      s++;
      while (isdigit(*s))
        wid = wid * 10 + (*s++ - '0');
      if (*s == '.')
      {
        s++;
        while (isdigit(*s))
          prec = prec * 10 + (*s++ - '0');
      }
      if (*s == 'd')
      {
        nbr = va_arg(ap, int);
        len_arg = ft_nbrlen(nbr);
        if (len_arg < wid && len_arg < prec)
        {
          if (wid > prec)
            wid = wid - prec + len_arg;
          else
            wid = len_arg;
        }
        for (int i = 0;i < wid - len_arg;i++)
          ft_putchar(' ');
        for (int j = 0;j < prec - len_arg;j++)
          ft_putchar('0');
        p = ft_itoa(nbr);
        ft_putstr(p);
        free(p);
        va_end(ap);
        s++;
      }
    }
  }
}
