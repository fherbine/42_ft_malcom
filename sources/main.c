#include "../includes/ft_malcom.h"

static t_malcom	*get_malcom_struct(void)
{
	t_malcom *mstruct = NULL;
	if (!(mstruct = (t_malcom *)malloc(sizeof(t_malcom))))
		exit(EXIT_FAILURE);
	
	ft_bzero(mstruct, sizeof(*mstruct));
	return (mstruct);
}

void	free_malcom_struct(t_malcom *mstruct)
{
	free(mstruct);
}

int main(int argc, char **argv)
{
	t_malcom *mstruct = get_malcom_struct();
	parse(argc, argv, mstruct);
	display_mstruct(mstruct);
}