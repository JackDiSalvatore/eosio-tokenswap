# Chestnut - Smart EOS accounts for automation and security.

We offer a multi-signature, smart contract enabled "Smart Account" which helps you create a set of rules and safeguards so that your EOS account secures and automates your finances.

One big obstacle to widespread adoption of crypto assets is the fear users have in taking responsibility for managing and protecting their own money. Chestnut takes some of the best security practices from the traditional banking system and bridges them over to the blockchain space, With this, users can feel the same level of safety they have become accustomed to with the autonomy and transparency that the blockchain offers.

Chestnut utilizes a smart contract within a multi-sig account to enable users to set specific and customizable rules or restrictions on the activity, size or type of transactions that can be executed on the account.

Similar to security and fraud protection offerings by traditional credit card companies, Chestnut users can set spending limits, whitelist/ blacklist recipients, freeze the account or nominate beneficiaries in case of emergencies. With Chestnut, users have the benefit of setting their own account rules rather than rules being imposed by a third party institution.

Each account transaction will be cross referenced through our smart contract and if it does not fit the set parameters, Chestnut will not sign off on the transaction as a multi-sig.

At no point does Chestnut require private information and we cannot make changes to a customer’s account unless the change was initiated by the customer.

Our service will be a subscription based model, with freemium/ premium offerings. Any rule that would require a query to the blockchain over a period of time would be a premium offering.

Chestnut will provide the peace of mind that so many blockchain curious members of the general public desire before taking the leap into the world of crypto assets.

# Prerequisites

Make sure Docker and Node.js are installed

-   Install Docker: https://docs.docker.com/docker-for-mac/install/
-   Install Node.js: https://nodejs.org/en/

The DApp and eosio will occupy the ports 3000, 8888 and 9876. Make sure nothing else is already running on these ports.

Clone the repository:

```sh
git clone https://github.com/liebeskind/chestnut-eos
```

The following guide assumes you are using macOS.

# Quick start - Run the DApp

**To start**

```sh
./quick_start.sh
```

The above command will execute the following in sequence:

1. `first_time_setup.sh`
2. `start_eosio_docker.sh`
3. `start_frontend.sh`

**To stop**, press `ctrl+c` on your keyboard, and execute:

```sh
docker stop eosio_securitylogic_container
```

# Detailed guide

In this section we will describe in detail each script used to run the Chestnut environment in details.

## Initial setup

```sh
./first_time_setup.sh
```

Executing the above shell script verifies that docker and node.js are installed. It then downloads the `eosio/eos-dev` docker image (which contains a full version of the eosio blockchain), removes any previous instances of this docker container and installs node packages for the frontend react app.

## Initialise and start blockchain and DApp

After the initialisation, two terminal windows are required, both opened in the repository directory

-   The **first terminal window** is for **blockchain** process.
-   The **second terminal window** is for **frontend** react app.

**running the blockchain**

For the first (blockchain) terminal window, run

```sh
./start_eosio_docker.sh
```

The log of blockchain will be displayed on your screen. eosio is now running and starts producing blocks.

**running the DApp**

For the second (frontend) terminal window, run

```sh
./start_frontend.sh
```

## Stopping blockchain or DApp

**stopping the blockchain**

In the first (blockchain) terminal window, press `ctrl+c` on your keyboard, the log will stop printing. And then execute:

```sh
docker stop eosio_securitylogic_container
```

This action will take a few seconds. The blockchain will be stopped.

**stopping the DApp**

In the second (frontend) terminal window, press `ctrl+c` on your keyboard. The frontend react app will be stopped.

## Restarting blockchain or DApp

**restarting the blockchain**

```sh
./restart.sh
```

## Reset blockchain data

First, you need to stop the blockchain (as above) and then execute:

```sh
./first_time_setup.sh
```

This removes all data on the blockchain, including accounts, deployed smart contracts, etc... The block count will be reset when you start the blockchain again.
