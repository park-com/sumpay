// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xc4;
        vAlertPubKey = ParseHex("04e6480b31b13352355cd4072def967e52d928130cb33eded45d995251e627b3ecbe6637cfab15dc7017fb4de258daebd89ed3adfb0a2867c1d723d039c4392e4a"); // pskbank
        nDefaultPort = 13800;   // pskbank
        nRPCPort = 13801;       // pskbank
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "2017/11/30 Politics: Trump Shares Inflammatory Anti-Muslim Videos, and Britain’s Leader Condemns Them"; // pskbank
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1512017192, vin, vout, 0);  // pskbank
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1512017192;  // pskbank
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 4379191;  // pskbank                                        

        hashGenesisBlock = genesis.GetHash(); 
        //=================================================================================

        // "mine" the nonce
        if(false) {
           std::cout << "search mainnet genesis blocks" << std::endl;
           for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
               if (genesis.nNonce % 1000000 == 0)
                   std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
               hashGenesisBlock = genesis.GetHash();
               unsigned char *b = hashGenesisBlock.end() - 3;
               if (memcmp(b, "\x01\x00\x00", 3) == 0) {
                   std::cout << "nNonce is: " << genesis.nNonce << std::endl;
                   std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                   std::cout << "Block is: " << genesis.ToString() << std::endl;
                   abort();
                   break;
               }
           }
        printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        }

        assert(hashGenesisBlock == uint256("0x00000153e8ba7c188e50dbc2da5060f290f2d61462892a7a020ffdf08832b17d"));
        assert(genesis.hashMerkleRoot == uint256("0x3c46987bbe1bb7baab4aa5962c55245a8590a0576fedc37f6c0263dfd1b94d4a"));

        //vSeeds.push_back(CDNSSeedData("seed1", "0.0.0.0"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);  // pskbank
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,43);  // pskbank
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,150);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = LAST_POW_BLOCK;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0x79;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xa2;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("046f791cd0652c59aea3f327e5d4fd816e32db1c9816a53a81ebff59c67bbabba4ca12204d1ea83d6795993e0398a6b435df1ff91a4ba7f93c6869dbd775789e0b");
        nDefaultPort = 23800;  // pskbank
        nRPCPort = 23801;      // pskbank
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 1497040584;
        genesis.nNonce = 7658;
		
        hashGenesisBlock = genesis.GetHash();

        //===============================================================================
        // "mine" the nonce
        if(false) {
           std::cout << "search testnet genesis blocks" << std::endl;
           for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
               if (genesis.nNonce % 1000000 == 0)
                   std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
               hashGenesisBlock = genesis.GetHash();
               unsigned char *b = hashGenesisBlock.end() - 2;
               if (memcmp(b, "\x00\x00", 2) == 0) {
                   std::cout << "testnet nNonce is: " << genesis.nNonce << std::endl;
                   std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                   std::cout << "Block is: " << genesis.ToString() << std::endl;
                   abort();
                   break;
               }
           }
       }
       //================================================================================

        assert(hashGenesisBlock == uint256("0x0000db992b5d1ba6e885ca3a9b3d51262be2bb815e23eb361636812b93922a9f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,229);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
