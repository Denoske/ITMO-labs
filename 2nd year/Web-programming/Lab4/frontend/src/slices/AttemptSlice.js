import { createSlice } from '@reduxjs/toolkit'

export const AttemptSlice = createSlice({
  name: 'attempts',
  initialState: {
    // value: null
    value: [],
    // value: [{x:10, y:10, r:10, doFitArea:false}, {x:10, y:10, r:10, doFitArea:false},],
  },
  reducers: {
    addAttempt: (state, action) => {
      state.value.push(action.payload);
    },
    removeAllAttempts: (state) => {
      state.value = [];
    },
  },
})

//selector function
export const selectAttempts = state => state.attempts.value;

// Action creators are generated for each case reducer function
export const {addAttempt, removeAllAttempts } = AttemptSlice.actions

export default AttemptSlice.reducer