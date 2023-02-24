import { configureStore } from '@reduxjs/toolkit';
import AttemptSlice from './slices/AttemptSlice.js';
import tokenSlice from './slices/tokenSlice.js';

export default configureStore({
    reducer: {
        token: tokenSlice,
        attempts: AttemptSlice,
    },
})