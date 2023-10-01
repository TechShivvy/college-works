#!/bin/bash
mkcd()
{
	mkdir $1 $2 $3
	cd ~/$3
}
mkcd $1 $2 $3
