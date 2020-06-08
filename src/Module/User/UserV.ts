import { FieldValidator } from '@a-a-game-studio/aa-components/lib';
import { UserLogin } from './UserR';


/**
 * Input data validator
 * @param data 
 * @param cValidator 
 */
export const faUserLoginV = (data: UserLogin.RequestI, cValidator: FieldValidator): FieldValidator => {

    cValidator.fSetData(data.login)
        .fSetErrorString('login')
        .fExist()
        .fMinLen(3)
        .fMaxLen(50);

    cValidator.fSetData(data.pswd)
        .fSetErrorString('paswd')
        .fExist()
        .fMinLen(3)
        .fMaxLen(50);

    if (!cValidator.fIsOk()) {
        throw 'error';
    }

    return cValidator;

}