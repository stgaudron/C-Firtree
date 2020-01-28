#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


static int	get_columns(int size)
{
  int		index_size;
  int		index_lines;
  int		max_lines;
  int		columns;

  columns = 1;
  index_size = 1;
  while (index_size < size)
    {
      max_lines = index_size + 3;
      index_lines = 1;
      while (index_lines < max_lines)
	{
	  columns = columns + 2;
	  index_lines = index_lines + 1;
	}
      index_size = index_size + 1;
      columns = columns - (index_size / 2) * 2;
    }
  return (columns);
}

static void	put_bottom(int size,
			   int total_max_columns,
			   int max_lines,
			   int index_lines)
{
  int		columns;
  int		index_columns;

  if (size % 2 == 1)
    columns = size;
  else
    columns = size + 1;
  while (index_lines <= max_lines)
    {
      index_columns = 1;
      while (index_columns < (total_max_columns - columns + 2) / 2)
	{
	  write(1, " ", 1);
	  index_columns = index_columns + 1;
	}
      index_columns = 1;
      while (index_columns <= columns)
	{
	  write(1, "|", 1);
	  index_columns = index_columns + 1;
	}
      write(1, "\n", 1);
      index_lines = index_lines + 1;
    }
}

static int	put_tree(int total_max_columns, int columns, int max_columns)
{
  int		index_columns;

  index_columns = 1;
  while (index_columns < (total_max_columns - columns + 2) / 2)
    {
      write(1, " ", 1);
      index_columns = index_columns + 1;
    }
  index_columns = 1;
  while (index_columns <= columns && columns <= max_columns)
    {
      write(1, "*", 1);
      index_columns = index_columns + 1;
    }
  write(1, "\n", 1);
  return (columns + 2);
}

static void	check_errors(int size)
{
  if (size == 0)
    {
      return ;
    }
  if (size < 0)
    {
      write(2, "The argument must be positive.\n", 31);
      return ;
    }
}

void	tree(int size)
{
  int	max_lines;
  int	total_max_lines;
  int	columns;
  int	index_lines;
  int	index_size;

  if (size <= 0)
    return (check_errors(size));
  total_max_lines = size + 3;
  index_size = 1;
  while (index_size <= size)
    {
      columns = get_columns(index_size);
      max_lines = index_size + 3;
      index_lines = 1;
      while (index_lines <= max_lines)
	{
	  columns = put_tree(get_columns(size) + total_max_lines * 2 - 2,
			     columns, columns * max_lines * 2);
	  index_lines = index_lines + 1;
	}
      index_size = index_size + 1;
    }
  put_bottom(size, get_columns(size) + total_max_lines * 2 - 2, size, 1);
}

int	main(int argc, char **argv)
{
  if (!argv[1])
  {
    write(2, "Requires an argument to size tree.\n", 36);
    return 0 ;
  }
tree(atoi(argv[1]));
}
