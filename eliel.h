#include <sys/types.h>
#include <unistd.h>

typedef struct s_proc
{
	int fd_in;       // Descripteur de fichier pour stdin
	int fd_out;      // Descripteur de fichier pour stdout
	int **pipe_fd;   // Tableau de descripteurs de fichier pour les pipes
	int *fd_heredoc; // Tableau de descripteurs de fichier pour les here-docs
	int n_heredoc;   // Nombre de here-doc dans la ligne de commande actuelle
	int n_pipes;     // Nombre de pipe dans la ligne de commande
	pid_t *pid;      // Tableau de PID pour la gestion des processus enfants
}	t_proc;

typedef struct s_cmd
{
	char *cmd;          // La commande de base a executer (ex : "ls", "cat"...)
	char *cmd_path;    
		// Chemin d'acces vers l'executable de la commande (ex : "/usr/bin",
		//"/usr/local/bin"...)
	char **opt;         // Options pour la commande (ex pour ls : "-l", "-a"...)
	char **token;       // Token de la ligne de commande (avis isma ?)
	int *type;          // Types de chaque token (avis isma ?)
	int index;          // Position de la commande dans la sequence de commandes
	struct s_cmd *next;
		// Pointeur vers la structure de commande suivante dans une sequence
}	t_cmd;

// (pour s_struct)
// manipulation de donnes, a ismael de voir pour le projet final
// (c'est ce que j'utilise pour parser au minimum pour comprendre le builtins et exec)
// (libre a toi de changer et d'ajouter des structures pour le parsing,
	//tant que les t_proc et s_cmd sont bien remplies)
typedef struct s_list
{
	char *str;           // Une chaine dans la liste,
		// peut representer une commande ou une donnee
	int type;            // Le type de l'element,
		// aide a decider du traitement de la chaine
	struct s_list *next; // Pointeur vers l'element de liste suivant
}	t_list;

typedef struct s_envp
{
	char **tab;         
		// Tableau de str contenant le nom et la valeur de chaque variable d'environnement
	struct s_envp *next;
		// Pointeur vers la structure de variable d'environnement suivante
}	t_envp;

typedef struct s_data
{
	t_cmd *cmd;    
		// Pointeur vers la premiere structure t_cmd dans une liste de commandes
	t_list *list;   // Pointeur vers la structure s_list
	t_envp *envp;  
		// Pointeur vers la premiere structure t_envp pour les variables d'environnement
	t_proc *proc;  
		// Pointeur vers la structure t_proc pour les donnees de processus
	char *env_path; // Chemin vers l'environnement pour trouver des executables
}	t_data;