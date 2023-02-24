import { createSlice } from '@reduxjs/toolkit'

export const tokenSlice = createSlice({
  name: 'token',
  initialState: {
    value: null,
  },
  reducers: {
    setToken: (state, action) => {
      state.value = action.payload;
    },
    resetToken: (state) => {
      state.value = null;
    },
  },
})

//selector function
export const selectToken = state => state.token.value;

// Action creators are generated for each case reducer function
export const {setToken, resetToken } = tokenSlice.actions;

export default tokenSlice.reducer;