MM Tools
========

Bootstrap:
`bash <(curl -s https://raw.githubusercontent.com/machbarmacher/mmtools/master/bootstrap/mm-init-server)`

Server wide tools:

* mmtools-help # this help
* Fixes local drush aliases
* drush dbcc # mmtools-db-caches-clean
* drush mmsi # mmtools-site-install
* ddrush # drush in docroot
* sdrush shop # drush in site 'shop'
* iam # tmux wrapper
* mariadb # uberspece mariadb helper
* rmf # remove by force... dangerous...
* uberdom # symlink and add arbitrary uberspace domain
* ubersubdom # symlink and add uberspace sub-domain
* unlock-settings # write-unprotect settings.php
* mm-prepare-server # some settings
* installation-init # require builder, runtime, revert
* mm-letsencrypt-renew # wraps uberspace certbot
