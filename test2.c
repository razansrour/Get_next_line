#include "get_next_line.h"

char    *get_line(t_list *list)
{
    int     str_len;
    char    *next_str;

    if (list == NULL)
        return (NULL);
}

/*
 * append one node
 * to the end of list
*/
void    append(t_list **list, char *buf)
{
    t_list  *new_node;
    t_list  *last_node;

    last_node = find_last_node(*list);
    new_node = malloc(sizeof(t_list));
    if (NULL == new_node)
        return ;
    //If the list is empty
    //if NULL == *list
    if (NULL == last_node)
        *list = new_node;
    else
        last_node->next = new_node;
    new_node->str_buf = buf;
    new_node->next = NULL;
}

void    create_list(t_list **list, int fd)
{
    //Necessary to place the \0 -> "string\0"
    int     char_read;
    char    *buf;

    // scan line if '\n' present
    while(!found_newline(*list))
    {
        buf = (char *)malloc(BUFFER_SIZE + 1);
        if (NULL == buf)
            return ;
        char_read = read(fd, buf, BUFFER_SIZE);
        if(!char_read)
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        // Append the node
        append(list, buf);
    }
}

char *get_next_line(int fd)
{
    static t_list   *list = NULL;
    char            *next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return (NULL);
    //Create my list till I stumble into '\n'
    create_list(&list, fd);
    if (NULL == list)
        return (NULL);
    //fetch the line from list    
    next_line = get_line(list);

    //
    polish_list(&list);
    return (next_line);
}

int main()
{
    int     fd;

    fd = open("file.txt", O_RDONLY);
    printf("results of get next line %s, fd = %d\n", get_next_line(fd), fd);
    return 0;
}