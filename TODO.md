TODO
====

* Cmd to add rewritebase / to .htaccess
* Cmd to install basic modules and tools to new drupal
  redis, adminmenu, 
* Cmd to add docroot symlink if needed
* Cmd to set PHP version
* Cmd to remove .git dirs: 
  find * -type d -name ".git" -print -exec rm -rf {} +
  and prevent them using 
* better: add .git to .gitignore
* add patch to drush:
          "patches": {
              "drush/drush": {
                  "mysql defaults-extra-file": "https://github.com/clever-systems/drush/commit/2acbbbc9a69b12e393ffd976614a8b2368b9a668.patch"
              }
          },
* fix ddrush to use drupal root
* and fix drupal root names in my installations

