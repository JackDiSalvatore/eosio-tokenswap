#!/usr/bin/env bash
set -o errexit

# set PATH
PATH="$PATH:/opt/eosio/bin"

CONTRACTSPATH="$( pwd -P )/contracts/eosio.contracts/build"

# unlock the wallet, ignore error if already unlocked
if [ ! -z $3 ]; then cleos wallet unlock -n $3 --password $4 || true; fi

# set (deploy) compiled contract to blockchain
cleos set contract $2 "$CONTRACTSPATH/$1/" --permission $2
