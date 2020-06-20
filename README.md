### prereqs
install R & pandoc

### howto build and deploy site
1. run the site generation script from shell:
`Rscript site-generate.R`

2. deploy to gh-pages:
`git subtree push --prefix site origin gh-pages`

### ghpages URL: https://mrobertson-csumb.github.io/portfolio-site