#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>

#include "../eosio.contracts/eosio.token/include/eosio.token/eosio.token.hpp"
#include "../eosio.contracts/eosio.token/src/eosio.token.cpp"

#define EOS_SYMBOL symbol("EOS", 4)
#define RAMCORE_SYMBOL symbol("RAMCORE", 4)
#define RAM_SYMBOL symbol("RAM", 0)


using namespace eosio;


CONTRACT tokenswap : public eosio::token {
  private:

    /****************************************************************************
     *                            F U N C T I O N S
     ***************************************************************************/

    time_point current_time_point() {
      const static time_point ct{ microseconds{ static_cast<int64_t>( current_time() ) } };
      return ct;
    }

    /****************************************************************************
     *                                T A B L E S
     ***************************************************************************/
    struct [[eosio::table]] account {
      asset    balance;

      uint64_t primary_key()const { return balance.symbol.code().raw(); }
    };

    struct [[eosio::table]] currency_stats {
      asset    supply;

      uint64_t primary_key()const { return supply.symbol.code().raw(); }
    };

    typedef eosio::multi_index< "accounts"_n, account >        accounts;
    typedef eosio::multi_index< "stat"_n,     currency_stats >    stats;

    // void sub_balance( name owner, asset value ) {
    //   accounts from_acnts( _self, owner.value );

    //   const auto& from = from_acnts.get( value.symbol.code().raw(), "no balance object found" );
    //   eosio_assert( from.balance.amount >= value.amount, "overdrawn balance" );

    //   from_acnts.modify( from, owner, [&]( auto& a ) {
    //         a.balance -= value;
    //      });
    // }

    // void add_balance( name owner, asset value, name ram_payer ) {
    //   accounts to_acnts( _self, owner.value );
    //   auto to = to_acnts.find( value.symbol.code().raw() );
    //   if( to == to_acnts.end() ) {
    //      to_acnts.emplace( ram_payer, [&]( auto& a ){
    //        a.balance = value;
    //      });
    //   } else {
    //     to_acnts.modify( to, same_payer, [&]( auto& a ) {
    //       a.balance += value;
    //     });
    //   }
    // }

  public:
    //using token::token;

    // constructor
    tokenswap( name receiver, name code, datastream<const char*> ds ):
                  eosio::token( receiver, code, ds ) {}


    /****************************************************************************
     *                              A C T I O N S
     ***************************************************************************/


    ACTION create( symbol sym ) {
      require_auth( _self );

      eosio_assert( sym.is_valid(), "invalid symbol name" );

      stats statstable( _self, sym.code().raw() );
      auto existing = statstable.find( sym.code().raw() );
      eosio_assert( existing == statstable.end(), "token with symbol already exists" );

      print("EMPLACING INTO EOS\n");
      statstable.emplace( _self, [&]( auto& s ) {
         s.supply = asset( 0, sym );
      });
    }


    ACTION issue( name to, asset quantity, string memo )
    {
        auto sym = quantity.symbol;
        eosio_assert( sym.is_valid(), "invalid symbol name" );
        eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

        stats statstable( _self, sym.code().raw() );
        auto existing = statstable.find( sym.code().raw() );
        eosio_assert( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
        const auto& st = *existing;

        // require_auth( st.issuer );
        eosio_assert( quantity.is_valid(), "invalid quantity" );
        eosio_assert( quantity.amount > 0, "must issue positive quantity" );

        eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
        // eosio_assert( quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

        statstable.modify( st, same_payer, [&]( auto& s ) {
           s.supply += quantity;
        });

        add_balance( to, quantity, to );

        // if( to != st.issuer ) {
        //   SEND_INLINE_ACTION( *this, transfer, { {st.issuer, "active"_n} },
        //                       { st.issuer, to, quantity, memo }
        //   );
        // }
    }


    ACTION deposit( name         from,
                    asset        quantity,
                    std::string  memo ) {
      action(
        permission_level{from,"active"_n},
        "eosio.token"_n,
        "transfer"_n,
        std::make_tuple( from, get_self(), quantity, memo )
      ).send();

// https://eosio.stackexchange.com/questions/1661/how-to-call-action-of-another-contract-within-a-contract

      action(
        permission_level{from,"active"_n},
        get_self(),
        "issue"_n,
        std::make_tuple( from, quantity, memo )
      ).send();
    }


    ACTION withdraw( name         from,
                     asset        quantity,
                     std::string  memo ) {
      action(
        permission_level{from,"active"_n},
        get_self(),
        "retire"_n,
        std::make_tuple( from, quantity, memo )
      ).send();

      action(
        permission_level{get_self(),"active"_n},
        "eosio.token"_n,
        "transfer"_n,
        std::make_tuple( get_self(), from, quantity, memo )
      ).send();
    }


    ACTION hello( void ) {
      print("hello world\n");
    }


    ACTION retire( name from, asset quantity, string memo )
    {
        auto sym = quantity.symbol;
        eosio_assert( sym.is_valid(), "invalid symbol name" );
        eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

        stats statstable( _self, sym.code().raw() );
        auto existing = statstable.find( sym.code().raw() );
        eosio_assert( existing != statstable.end(), "token with symbol does not exist" );
        const auto& st = *existing;

        require_auth( from );
        eosio_assert( quantity.is_valid(), "invalid quantity" );
        eosio_assert( quantity.amount > 0, "must retire positive quantity" );

        eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );

        statstable.modify( st, same_payer, [&]( auto& s ) {
           s.supply -= quantity;
        });

        sub_balance( from, quantity );
    }


};

// specify the contract name, and export a public action: update
//EOSIO_DISPATCH( tokenswap, (update)(transfer) )

extern "C" {
  void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
    // tokenswap _accountmaker(receiver);
    //auto self = receiver;

    if( code==receiver && action== name("hello").value ) {
      execute_action( name(receiver), name(code), &tokenswap::hello );
    }
    else if(code==receiver && action== name("create").value) {
      execute_action(name(receiver), name(code), &tokenswap::create );
    }
    else if(code==receiver && action== name("deposit").value) {
      execute_action(name(receiver), name(code), &tokenswap::deposit );
    }
    else if(code==receiver && action== name("withdraw").value) {
      execute_action(name(receiver), name(code), &tokenswap::withdraw );
    }
    // else if( code==receiver && action== name("transfer").value ) {
    //   execute_action( name(receiver), name(code), &tokenswap::transfer );
    // }
    else if(code==receiver && action== name("issue").value) {
      execute_action(name(receiver), name(code), &tokenswap::issue );
    }
    else if(code==receiver && action== name("retire").value) {
      execute_action(name(receiver), name(code), &tokenswap::retire );
    }
    // else if(code==receiver && action== name("open").value) {
    //   execute_action(name(receiver), name(code), &tokenswap::open );
    // }
    // else if(code==receiver && action== name("close").value) {
    //   execute_action(name(receiver), name(code), &tokenswap::close );
    // }
  }
};
