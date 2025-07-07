# Pipex

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![System](https://img.shields.io/badge/System-Unix-red.svg)](https://en.wikipedia.org/wiki/Unix)

## 📖 Description

**Pipex** est un projet de l'école 42 qui reproduit le comportement des pipes Unix en C. Ce programme simule l'exécution de deux commandes reliées par un pipe, équivalent à la commande shell :

```bash
< file1 cmd1 | cmd2 > file2
```

Le projet permet de comprendre en profondeur les mécanismes des processus Unix, des pipes, des redirections et de la communication inter-processus (IPC).

## ✨ Fonctionnalités

### 🔧 Fonctionnalités principales
- **Simulation de pipes Unix** : Reproduction fidèle du comportement des pipes système
- **Gestion des processus** : Création et synchronisation de processus enfants avec `fork()`
- **Redirections I/O** : Gestion des entrées/sorties avec `dup2()`
- **Recherche de commandes** : Résolution automatique des chemins d'exécution via `$PATH`
- **Gestion d'erreurs robuste** : Traitement complet des cas d'erreur système

### 🛠️ Aspects techniques
- **Communication inter-processus** : Utilisation des pipes pour la communication
- **Gestion mémoire** : Allocation et libération propre de toutes les ressources
- **Parsing d'arguments** : Analyse et validation des paramètres d'entrée
- **Exécution de commandes** : Lancement de programmes externes avec `execve()`

## 🔧 Prérequis

### Système
- **OS** : Unix/Linux (testé sur Ubuntu/Debian)
- **Compilateur** : GCC ou Clang avec support C99
- **Make** : Pour la compilation automatisée

### Bibliothèques système
```bash
# Les bibliothèques suivantes sont requises (généralement préinstallées)
- unistd.h    # Appels système Unix
- sys/wait.h  # Gestion des processus
- fcntl.h     # Contrôle des fichiers
- errno.h     # Gestion des erreurs
```

## 🚀 Installation

### 1. Clonage du projet
```bash
git clone [URL_DU_REPO]
cd pipex
```

### 2. Compilation
```bash
# Compilation complète (libft + pipex)
make

# Nettoyage des fichiers objets
make clean

# Nettoyage complet
make fclean

# Recompilation complète
make re
```

### 3. Vérification
```bash
# L'exécutable pipex doit être créé à la racine
ls -la pipex
```

## 🎯 Utilisation

### Syntaxe
```bash
./pipex file1 cmd1 cmd2 file2
```

### Paramètres
- **file1** : Fichier d'entrée (équivalent à `< file1`)
- **cmd1** : Première commande à exécuter
- **cmd2** : Deuxième commande à exécuter
- **file2** : Fichier de sortie (équivalent à `> file2`)

### Exemples d'utilisation

#### Exemple 1 : Compter les lignes d'un fichier
```bash
# Équivalent à : < input.txt cat | wc -l > output.txt
./pipex input.txt "cat" "wc -l" output.txt
```

#### Exemple 2 : Filtrer et trier
```bash
# Équivalent à : < data.txt grep "pattern" | sort > sorted.txt
./pipex data.txt "grep pattern" "sort" sorted.txt
```

#### Exemple 3 : Traitement de texte
```bash
# Équivalent à : < file.txt head -n 10 | tail -n 5 > result.txt
./pipex file.txt "head -n 10" "tail -n 5" result.txt
```

#### Exemple 4 : Avec chemins absolus
```bash
# Utilisation de chemins complets pour les commandes
./pipex input.txt "/bin/cat" "/usr/bin/wc -l" output.txt
```

## 🏗️ Architecture du code

```
pipex/
├── srcs/
│   ├── main.c          # Point d'entrée et validation des arguments
│   ├── ft_pipex.c      # Logique principale des pipes et processus
│   ├── ft_path.c       # Gestion des chemins et résolution des commandes
│   └── ft_free.c       # Gestion mémoire et nettoyage
├── includes/
│   └── pipex.h         # Définitions et prototypes
├── libft/              # Bibliothèque personnelle
└── Makefile           # Compilation automatisée
```

### Modules détaillés

#### 🎮 Main (`srcs/main.c`)
- **Validation des arguments** : Vérification du nombre de paramètres
- **Initialisation des commandes** : Préparation des structures de données
- **Orchestration** : Appel de la fonction principale pipex
- **Nettoyage final** : Libération des ressources

#### 🔄 Pipex (`srcs/ft_pipex.c`)
- **init_all()** : Initialisation des structures
- **init_cmd()** : Préparation d'une commande (parsing, résolution de chemin)
- **child_one()** : Processus enfant pour la première commande
- **child_two()** : Processus enfant pour la deuxième commande
- **pipex()** : Fonction principale gérant les pipes et processus

#### 🛣️ Path (`srcs/ft_path.c`)
- **get_path()** : Extraction de la variable d'environnement PATH
- **init_pathes()** : Initialisation des chemins de recherche
- **find_cmd_path()** : Recherche du chemin complet d'une commande
- **ft_three_join()** : Concaténation de trois chaînes

#### 🧹 Free (`srcs/ft_free.c`)
- **ft_free_split()** : Libération d'un tableau de chaînes
- **free_cmd()** : Libération d'une structure de commande
- **free_all_and_exit()** : Nettoyage complet et sortie d'urgence

## 🔍 Fonctionnement interne

### 1. **Parsing et validation**
```c
// Vérification des arguments
if (argc != 5)
    exit_with_error("Invalid number of arguments");
```

### 2. **Initialisation des commandes**
```c
// Parsing de "ls -la" -> ["ls", "-la"]
data->command = ft_split(arg, ' ');
data->base = data->command[0];  // "ls"
```

### 3. **Résolution des chemins**
```c
// Recherche dans PATH : /bin/ls, /usr/bin/ls, etc.
find_cmd_path(data);
```

### 4. **Création du pipe**
```c
int fd[2];
pipe(fd);  // fd[0] = lecture, fd[1] = écriture
```

### 5. **Processus enfants**
```c
// Premier enfant : file1 -> cmd1 -> pipe
child_one: dup2(infile, STDIN) + dup2(pipe[1], STDOUT)

// Deuxième enfant : pipe -> cmd2 -> file2  
child_two: dup2(pipe[0], STDIN) + dup2(outfile, STDOUT)
```

## 🧪 Tests et exemples

### Tests de base
```bash
# Test simple
echo "Hello World" > test.txt
./pipex test.txt "cat" "wc -w" output.txt
cat output.txt  # Devrait afficher : 2

# Test avec grep
echo -e "apple\nbanana\napricot" > fruits.txt
./pipex fruits.txt "grep ap" "wc -l" count.txt
cat count.txt  # Devrait afficher : 2
```

### Tests d'erreur
```bash
# Fichier d'entrée inexistant
./pipex nonexistent.txt "cat" "wc -l" output.txt

# Commande invalide
./pipex input.txt "invalidcmd" "wc -l" output.txt

# Nombre d'arguments incorrect
./pipex input.txt "cat"  # Erreur : pas assez d'arguments
```

### Comparaison avec le shell
```bash
# Commande shell originale
< input.txt grep "pattern" | sort > shell_output.txt

# Équivalent pipex
./pipex input.txt "grep pattern" "sort" pipex_output.txt

# Vérification
diff shell_output.txt pipex_output.txt  # Devrait être identique
```

## 📝 Gestion des erreurs

Le programme gère de manière robuste les erreurs suivantes :

### Erreurs d'arguments
- ❌ **Nombre incorrect** : Exactement 4 arguments requis
- ❌ **Fichier d'entrée** : Fichier inexistant ou non lisible
- ❌ **Commandes invalides** : Commande introuvable dans PATH

### Erreurs système
- ❌ **Pipe** : Échec de création du pipe
- ❌ **Fork** : Échec de création de processus
- ❌ **Dup2** : Échec de redirection
- ❌ **Execve** : Échec d'exécution de commande
- ❌ **Open** : Échec d'ouverture de fichier

### Gestion mémoire
- ✅ **Libération automatique** : Toutes les allocations sont libérées
- ✅ **Sortie propre** : Nettoyage en cas d'erreur
- ✅ **Pas de fuites** : Gestion rigoureuse de la mémoire

## 🔧 Détails techniques

### Structures de données
```c
typedef struct s_data
{
    char    **command;  // Commande parsée ["ls", "-la"]
    char    *base;      // Nom de base "ls"
    char    *path;      // Chemin complet "/bin/ls"
    char    **pathes;   // Chemins PATH ["/bin", "/usr/bin", ...]
    char    **arr;      // Arguments pour execve
    char    **envp;     // Variables d'environnement
} t_data;
```

### Flux de données
```
[file1] → [cmd1] → [pipe] → [cmd2] → [file2]
   ↓         ↓        ↓        ↓        ↓
 open()   fork()   pipe()   fork()   open()
         execve()          execve()
```

## 🚀 Optimisations et améliorations

### Fonctionnalités avancées possibles
- **Support multi-pipes** : Chaînage de plus de 2 commandes
- **Gestion des signaux** : Interruption propre avec Ctrl+C
- **Mode verbose** : Affichage détaillé des opérations
- **Validation avancée** : Vérification des permissions d'exécution

### Optimisations de performance
- **Cache des chemins** : Mémorisation des chemins résolus
- **Parsing optimisé** : Amélioration du parsing des arguments
- **Gestion d'erreurs** : Messages d'erreur plus détaillés

## 📚 Concepts Unix appris

Ce projet permet de maîtriser :
- **Processus** : `fork()`, `wait()`, `waitpid()`
- **Pipes** : `pipe()`, communication inter-processus
- **Redirections** : `dup2()`, gestion des descripteurs de fichiers
- **Exécution** : `execve()`, remplacement de processus
- **Système de fichiers** : `open()`, `close()`, `access()`
- **Variables d'environnement** : Utilisation de `PATH`

## 👨‍💻 Auteur

**Etienne** - [edesaint@student.42.fr](mailto:edesaint@student.42.fr)

## 📄 Licence

Ce projet est développé à des fins éducatives dans le cadre de l'école 42.

---

*Maîtrisez les pipes Unix comme un pro ! 🔧⚡*
