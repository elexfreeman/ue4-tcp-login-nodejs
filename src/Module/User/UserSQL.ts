import BaseSQL from "../Sys/BaseSQL";
import { UserE, UserTokenE, UserI } from "./UserE";
import * as HashFunc from "../../Lib/HashFunc";

export class UserSQL extends BaseSQL {


    /**
     * Gives a token by login and password
     * @param login 
     * @param pass 
     * @returns token
     */
    public async faGetTokenByLoginAndPass(sLogin: string, sPass: string): Promise<string> {
        let res = '';

        let sql = `
            SELECT ut.token FROM ${UserE.NAME} u
            JOIN ${UserTokenE.NAME} ut ON u.id=ut.id_user
            WHERE            
                u.login= :login
            AND
                u.pswd= :pswd 
            LIMIT 1
        `;

        try {
            let result = await this.db.raw(sql, {
                'login': sLogin,
                //'pswd': HashFunc.fPassToHash(sPass),  // example
                'pswd': sPass,
            });
            res = result[0][0]['token'];
        } catch (e) {
            this.errorSys.errorEx(e, 'get_token_by_login_and_pass', 'Failed to get token by login and password');
        }

        return res;
    }


    /**
     * Gives a user
     * @param login 
     * @param pass 
     * @returns token
     */
    public async faGetUserInfoByToken(sToken: string): Promise<UserI> {
        let res: UserI;

        let sql = `
            SELECT u.id, u.user_name, u.login FROM ${UserE.NAME} u
            JOIN ${UserTokenE.NAME} ut ON u.id=ut.id_user
            WHERE            
                ut.token = :token
            LIMIT 1
        `;

        try {
            let result = await this.db.raw(sql, {
                'token': sToken,
            });
            res = result[0][0];
        } catch (e) {
            this.errorSys.errorEx(e, 'get_user_info_by_token', 'Failed to get user by token');
        }

        return res;
    }

}