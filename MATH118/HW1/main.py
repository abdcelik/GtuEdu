import pandas as pd
import numpy as np

if __name__ == "__main__":
    df = pd.read_csv('owid-covid-data.csv')
    pd.set_option("display.max_rows", None, "display.max_columns", None)
    f = open("output.txt", "w")

    countries_list = df['location'].tolist()
    countries_set = set(countries_list)

    q1 = len(countries_set)
    f.write("1. How many countries the dataset has?\n")
    f.write(str(q1))
    f.write("\n\n")

    countries = df.groupby(['location'])
    date_earliest = countries.agg(Date = ('date', np.min))

    q2 = date_earliest[date_earliest.eq(date_earliest.min()).any(1)]
    f.write("2. When is the earliest date data are taken for a country? Which country is it?\n")
    f.write(q2.to_string())
    f.write("\n\n")

    q3 = countries.agg(total_cases = ('total_cases', np.max))
    f.write("3. How many cases are confirmed for each country so far? Print pairwise results of country and total cases?\n")
    f.write(q3.to_string())
    f.write("\n\n")

    q4 = countries.agg(total_cases = ('total_deaths', np.max))
    f.write("4. How many deaths are confirmed for each country so far? Print pairwise results of country and total deaths.\n")
    f.write(q4.to_string())
    f.write("\n\n")

    q5 = countries.agg(min = ('reproduction_rate', np.min), max = ('reproduction_rate', np.max), avg = ('reproduction_rate', np.mean), var = ('reproduction_rate', np.var))
    f.write("5. What are the average, minimum, maximum and variation values of the reproduction rates for each country?\n")
    f.write(q5.to_string())
    f.write("\n\n")

    q6 = countries.agg(min = ('icu_patients', np.min), max = ('icu_patients', np.max), avg = ('icu_patients', np.mean), var = ('icu_patients', np.var))
    f.write("6. What are the average, minimum, maximum and variation values of the icu patients (intensive care unit patients) for each country?\n")
    f.write(q6.to_string())
    f.write("\n\n")

    q7 = countries.agg(min = ('hosp_patients', np.min), max = ('hosp_patients', np.max), avg = ('hosp_patients', np.mean), var = ('hosp_patients', np.var))
    f.write("7. What are the average, minimum, maximum and variation values of the hosp patients (hospital patients) for each country?\n")
    f.write(q7.to_string())
    f.write("\n\n")

    q8 = countries.agg(min = ('weekly_icu_admissions', np.min), max = ('weekly_icu_admissions', np.max), avg = ('weekly_icu_admissions', np.mean), var = ('weekly_icu_admissions', np.var))
    f.write("8. What are the average, minimum, maximum and variation values of the weekly icu (intensive care unit) admissions for each country?\n")
    f.write(q8.to_string())
    f.write("\n\n")

    q9 = countries.agg(min = ('weekly_hosp_admissions', np.min), max = ('weekly_hosp_admissions', np.max), avg = ('weekly_hosp_admissions', np.mean), var = ('weekly_hosp_admissions', np.var))
    f.write("9. What are the average, minimum, maximum and variation values of the weekly hospital admissions for each country?\n")
    f.write(q9.to_string())
    f.write("\n\n")

    q10 = countries.agg(min = ('new_tests', np.min), max = ('new_tests', np.max), avg = ('new_tests', np.mean), var = ('new_tests', np.var))
    f.write("10. What are the average, minimum, maximum and variation values of new tests per day for each country?\n")
    f.write(q10.to_string())
    f.write("\n\n")

    q11 = countries.agg(total_test = ('total_tests', np.max))
    f.write("11. How many tests are conducted in total for each country so far?\n")
    f.write(q11.to_string())
    f.write("\n\n")

    q12 = countries.agg(min = ('positive_rate', np.min), max = ('positive_rate', np.max), avg = ('positive_rate', np.mean), var = ('positive_rate', np.var))
    f.write("12. What are the average, minimum, maximum and variation values of the positive rates of the tests for each country?\n")
    f.write(q12.to_string())
    f.write("\n\n")

    q13 = countries.agg(min = ('tests_per_case', np.min), max = ('tests_per_case', np.max), avg = ('tests_per_case', np.mean), var = ('tests_per_case', np.var))
    f.write("13. What are the average, minimum, maximum and variation values of the tests per case for each country?\n")
    f.write(q13.to_string())
    f.write("\n\n")

    q14 = countries.agg(People_Fully_Vaccianated = ('people_vaccinated', np.max))
    f.write("14. How many people are vaccinated by at least one dose in each country?\n")
    f.write(q14.to_string())
    f.write("\n\n")

    q15 = countries.agg(People_Fully_Vaccianated = ('people_fully_vaccinated', np.max))
    f.write("15. How many people are vaccinated fully in each country?\n")
    f.write(q15.to_string())
    f.write("\n\n")

    q16 = countries.agg(total_vaccinations = ('total_vaccinations', np.max))
    f.write("16. How many vaccinations are administered in each country so far?\n")
    f.write(q16.to_string())
    f.write("\n\n")

    q17 = countries.agg(population = ('population', np.max), median_age = ('median_age', np.max), aged_65_older = ('aged_65_older', np.max), aged_70_older = ('aged_70_older', np.max), gdp_per_capita = ('gdp_per_capita', np.max), cardiovasc_death_rate = ('cardiovasc_death_rate',np.max), diabetes_prevalence = ('diabetes_prevalence',np.max), female_smokers = ('female_smokers', np.max), male_smokers = ('male_smokers', np.max), handwashing_facilities = ('handwashing_facilities', np.max), hospital_beds_per_thousand = ('hospital_beds_per_thousand', np.max), life_expectancy = ('life_expectancy', np.max), human_development_index = ('human_development_index', np.max))
    f.write("17. List information about population, median age, # of people aged 65 older, # of people aged 70 older, economic performance, death rates due to heart disease, diabetes prevalence, # of female smokers, # of male smokers, handwashing facilities, hospital beds per thousand people, life expectancy and human development index.\n")
    f.write(q17.to_string())
    f.write("\n\n")

    f.write("18. Summarize all the results that you obtain by the first 17 questions (except question 2).\n")
    q18 = pd.concat([q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17], axis = 1)
    q18.columns = ['q#3', 'q#4', 'q#5_min', 'q#5_max', 'q#5_avg', 'q#5_var', 'q#6_min', 'q#6_max', 'q#6_avg', 'q#6_var', 'q#7_min', 'q#7_max', 'q#7_avg', 'q#7_var','q#8_min', 'q#8_max', 'q#8_avg', 'q#8_var', 'q#9_min', 'q#9_max', 'q#9_avg', 'q#9_var', 'q#10_min', 'q#10_max', 'q#10_avg', 'q#10_var', 'q#11', 'q#12_min', 'q#12_max', 'q#12_avg', 'q#12_var', 'q#13_min', 'q#13_max', 'q#13_avg', 'q#13_var', 'q#14', 'q#15', 'q#16', 'q#17_population', 'q#17_median_age', 'q#17_aged_65_older', 'q#17_aged_70_older', 'q#17_economic performance', 'q#17_death_rates_due_to_heart_disease', 'q#17_diabetes_prevalence', 'q#17_female_smokers', 'q#17_male_smokers', 'q#17_handwashing_facilities', 'q#17_hospital_beds_per_thousand_people', 'q#17_life_expectancy', 'q#17_human_development_index']
    f.write(q18.to_string())
    f.write("\n\n")
    
    f.close()