# bbclib

The aim of this repository changed over the time. It became a field of experimentation with C, Noweb and LaTeX.

The result can be seen here : [bbclib.pdf](https://github.com/BernardTatin/bbclib/blob/v1.0.0/src/structures/noweb/bbclib.pdf)

## using `noweb`

To generate the code :

```shell
notangle rbuffer.nw > rbuffer.h
```

To generate the documentation :

```shell
noweave -delay -index rbuffer.nw > rbuffer.tex
```
