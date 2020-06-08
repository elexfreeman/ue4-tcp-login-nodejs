
import * as AAClasses from '@a-a-game-studio/aa-classes/lib';


/**
 * Knex Query Writing Wrapper
 */
export class KnexSys {

    public errorSys: AAClasses.Components.ErrorSys;

    constructor(errorSys: AAClasses.Components.ErrorSys) {
        this.errorSys = errorSys;
    }

    /**
     * Get string from SQL raw query
     * @param data
     */
    fOneRaw(data: any): any {
        let ok = this.errorSys.isOk();
        let one = null;

        if (ok) { // We get the base row LIMIT 1
            try {
                one = data[0][0];
            } catch (e) {
                throw this.errorSys.throwDB(e, 'faOneRaw');
            }
        }

        return one;
    }

    /**
     * Get list from SQL raw query
     * @param data
     */
    async fListRaw(data: any): Promise<any> {
        let list = null;

        if (this.errorSys.isOk()) {
            try {
                list = data[0];
            } catch (e) {
                throw this.errorSys.throwDB(e, 'fListRaw');
            }
        }

        return list;
    }

    /**
     * Get field from SQL raw query
     * @param data
     * @param sField
     */
    fFieldRaw(sField: string, data: any): number | string | boolean | bigint {
        let ok = this.errorSys.isOk();
        let field = null;

        if (this.errorSys.isOk()) {
            try { 
                field = data[0][0][sField];
            } catch (e) {
                throw this.errorSys.throwDB(e, 'fFieldRaw');
            }
        }

        return field;
    }

    // ==========================================

    /**
     * Get row from SQL builder query
     * @param data
     */
    async fOne(data: any): Promise<any> {
        let ok = this.errorSys.isOk();
        let one = null;

        if (this.errorSys.isOk()) {
            try { 
                one = data[0];
            } catch (e) {
                throw this.errorSys.throwDB(e, 'fOne');
            }
        }

        return one;
    }

    /**
     * List
     * @param data
     */
    async fList(data: any): Promise<any> {
        let list = null;

        if (this.errorSys.isOk()) {
            try { 
                list = data;
            } catch (e) {
                throw this.errorSys.throwDB(e, 'fList');
            }
        }

        return list;
    }

    /**
     * Get field from SQL builder query
     * @param sField
     * @param data
     */
    async fField(sField: string, data: any): Promise<number | string | boolean | bigint> {
        let ok = this.errorSys.isOk();
        let field = null;

        if (this.errorSys.isOk()) {
            try { 
                field = data[0][sField];
            } catch (e) {
                throw this.errorSys.throwDB(e, 'fField');
            }
        }

        return field;
    }
}
