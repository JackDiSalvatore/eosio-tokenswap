echo '=== hello world ==='
cleos push action tokenswap hello '[""]' -p tokenswap
cleos get account tokenswap

sleep 1

echo '=== create EOS token to hold ==='
cleos push action tokenswap create '["4,EOS"]' -p tokenswap
sleep 1
echo 'get table tokenswap EOS stat'
cleos get table tokenswap EOS stat
echo 'get table eosio.token tokenswap accounts'
cleos get table eosio.token tokenswap accounts
echo 'get table eosio.token daniel accounts'
cleos get table eosio.token daniel accounts

echo '=== daniel deposits 50.0000 EOS ==='
echo 'push action tokenswap deposit ["daniel","50.0000 EOS","my first deposit"] -p daniel'
cleos push action tokenswap deposit '["daniel","50.0000 EOS","my first deposit"]' -p daniel

sleep 1

echo '=== get table CHESTNUT ==='
echo 'get table tokenswap EOS stat'
cleos get table tokenswap EOS stat

echo 'get table tokenswap tokenswap accounts'
cleos get table tokenswap tokenswap accounts

echo 'get table tokenswap daniel accounts'
cleos get table tokenswap daniel accounts

echo '=== get table EOSIO.TOKEN ==='
echo 'get table eosio.token tokenswap accounts'
cleos get table eosio.token tokenswap accounts

echo 'get table eosio.token daniel accounts'
cleos get table eosio.token daniel accounts


echo '=== daniel withdraws 25.0000 EOS ==='
echo 'push action tokenswap withdraw ["daniel","25.0000 EOS","its my money and I want it now!"] -p daniel'
cleos push action tokenswap withdraw '["daniel","25.0000 EOS","its my money and I want it now!"]' -p daniel

sleep 1

echo '=== get table CHESTNUT ==='
echo 'get table tokenswap EOS stat'
cleos get table tokenswap EOS stat

echo 'get table tokenswap tokenswap accounts'
cleos get table tokenswap tokenswap accounts

echo 'get table tokenswap daniel accounts'
cleos get table tokenswap daniel accounts

echo '=== get table EOSIO.TOKEN ==='
echo 'get table eosio.token tokenswap accounts'
cleos get table eosio.token tokenswap accounts

echo 'get table eosio.token daniel accounts'
cleos get table eosio.token daniel accounts

